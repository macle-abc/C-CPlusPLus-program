#include "DataSystem.h"

DataSystem dataSystem;

void InitDataSystem(DataSystem* tempDataSystem)
{
	Student_list_init(&tempDataSystem->m_studentTable);
	Course_list_init(&tempDataSystem->m_courseTable);
	OptCourse_list_init(&tempDataSystem->m_optCourseTable);
	tempDataSystem->m_studentTable.set_copyer(CopyStu);
	tempDataSystem->m_studentTable.set_destructor(DestructStu);
	tempDataSystem->m_courseTable.set_copyer(CopyCourse);
	tempDataSystem->m_courseTable.set_destructor(DestructCourse);
	tempDataSystem->m_optCourseTable.set_copyer(CopyOpt);
	tempDataSystem->m_optCourseTable.set_destructor(DestructOpt);
}




void ForeachDataSystemByCondition(const DataSystem * dataSystem, DataType dataType, HelpSearchAndSavePointer help, bool(*condition)(const void * data1, const void * data2), const void * conArg2, DataSystem* result)
{
	Student_list_iterator sit = dataSystem->m_studentTable.begin((Student_list*)&dataSystem->m_studentTable);
	Course_list_iterator cit = dataSystem->m_courseTable.begin((Course_list*)&dataSystem->m_courseTable);
	OptCourse_list_iterator oit = dataSystem->m_optCourseTable.begin((OptCourse_list*)&dataSystem->m_optCourseTable);
	if (dataType == student)
	{
		while (sit != dataSystem->m_studentTable.end((Student_list*)&dataSystem->m_studentTable))
		{
				help(result, condition, student, sit, conArg2);
				sit = dataSystem->m_studentTable.next((Student_list*)&dataSystem->m_studentTable, sit);
		}
	}
	if (dataType == course)
	{
		while (cit != dataSystem->m_courseTable.end((Course_list*)&dataSystem->m_courseTable))
		{
			help(result, condition, course, cit, conArg2);
			cit = dataSystem->m_courseTable.next((Course_list*)&dataSystem->m_courseTable, cit);
		}

	}
	if (dataType == optCourse)
	{
		while (oit != dataSystem->m_optCourseTable.end((OptCourse_list*)&dataSystem->m_optCourseTable))
		{
			help(result, condition, optCourse, oit, conArg2);
			oit = dataSystem->m_optCourseTable.next((OptCourse_list*)&dataSystem->m_optCourseTable, oit);
		}
	}
}

void PrintfDataSystemToString(const DataSystem * dataSystem, mystring* text) 
{
	Student_list_iterator sit = dataSystem->m_studentTable.begin((Student_list*)&dataSystem->m_studentTable);
	Course_list_iterator cit = dataSystem->m_courseTable.begin((Course_list*)&dataSystem->m_courseTable);
	OptCourse_list_iterator oit = dataSystem->m_optCourseTable.begin((OptCourse_list*)&dataSystem->m_optCourseTable);
	char buff[1024] = { 0 };
	text->clear(text);
	//typedef struct Student
	//{
	//	unsigned int m_id;//学号
	//	string m_name;//姓名
	//	unsigned int m_class;//班级
	//	string m_major;//专业
	//	char m_sex;//性别
	//}Student;
	//typedef struct OptCourse
	//{
	//	unsigned int m_sId;//学号
	//	string m_cId;//课程号
	//	double m_score;//该科成绩
	//}OptCourse;
	//typedef struct Couse
	//{
	//	string m_cId;//课程号
	//	string m_cName;//课程名
	//	string m_teacher;//教师名
	//}Course;
	while (sit != dataSystem->m_studentTable.end((Student_list*)&dataSystem->m_studentTable))
	{
	//	sprintf(buff, "%20s%15u%10u%20s%5c\n", sit->m_name, sit->m_id, sit->m_class, sit->m_major, sit->m_sex);
		sprintf(buff, "%-20s%-15u%-10u%-20s%-5c\n", sit->m_name, sit->m_id, sit->m_class, sit->m_major, sit->m_sex);
		text->append(text, buff);
		sit = dataSystem->m_studentTable.next((Student_list*)&dataSystem->m_studentTable, sit);
	}
	while (cit != dataSystem->m_courseTable.end((Course_list*)&dataSystem->m_courseTable))
	{
//		sprintf(buff, "%15s%15s%15s\n", cit->m_cId, cit->m_cName, cit->m_teacher);
		sprintf(buff, "%-15s%-15s%-15s\n", cit->m_cId, cit->m_cName, cit->m_teacher);
		text->append(text, buff);
		cit = dataSystem->m_courseTable.next((Course_list*)&dataSystem->m_courseTable, cit);
	}
	while (oit != dataSystem->m_optCourseTable.end((OptCourse_list*)&dataSystem->m_optCourseTable))
	{
	//	sprintf(buff, "%15u%15s%5.2lf\n", oit->m_sId, oit->m_cId, oit->m_score);
		sprintf(buff, "%-15u%-15s%-5.2lf\n", oit->m_sId, oit->m_cId, oit->m_score);
		text->append(text, buff);
		oit = dataSystem->m_optCourseTable.next((OptCourse_list*)&dataSystem->m_optCourseTable, oit);
	}
}

void ClearDataSystemMember(DataSystem* des, DataType dataType)
{
	if (dataType == course)
		des->m_courseTable.clear(&des->m_courseTable);
	if (dataType == optCourse)
		des->m_optCourseTable.clear(&des->m_optCourseTable);
	if (dataType == student)
		des->m_studentTable.clear(&des->m_studentTable);
}

static bool copyCon(const void* data1, const void* data2)
{
	return TRUE;
}

static void help(DataSystem* data, bool(*ConditionSearch)(const void* data, const void* con), DataType dataType, const void* conArg1, const void* conArg2)
{
	if (dataType == course)
	{
		data->m_courseTable.push_back(&data->m_courseTable, (const Course*)conArg1);
	}
	if (dataType == optCourse)
	{
		data->m_optCourseTable.push_back(&data->m_optCourseTable, (const OptCourse*)conArg1);
	}
	if (dataType == student)
	{
		data->m_studentTable.push_back(&data->m_studentTable, (const Student*)conArg1);
	}
}
void CopyDataSystem(DataSystem* des, const DataSystem * src, DataType dataType)
{
	if (dataType == course)
	{
		ForeachDataSystemByCondition(src, course, help, copyCon, (const void*)NULL, des);
	}
	if (dataType == optCourse)
	{
		ForeachDataSystemByCondition(src, optCourse, help, copyCon, (const void*)NULL, des);
	}
	if (dataType == student)
	{
		ForeachDataSystemByCondition(src, student, help, copyCon, (const void*)NULL, des);
	}
}

void ClearDataSystem(DataSystem* des)
{
	ClearDataSystemMember(des, student);
	ClearDataSystemMember(des, optCourse);
	ClearDataSystemMember(des, course);
}

void DestroyDataSystemMember(DataSystem* des, DataType dataType)
{
	if (dataType == course)
		des->m_courseTable.destroy(&des->m_courseTable);
	if (dataType == optCourse)
		des->m_optCourseTable.destroy(&des->m_optCourseTable);
	if (dataType == student)
		des->m_studentTable.destroy(&des->m_studentTable);
}

void DestroyDataSystem(DataSystem* des)
{
	DestroyDataSystemMember(des, student);
	DestroyDataSystemMember(des, optCourse);
	DestroyDataSystemMember(des, course);
}

void ReadFileToDataSystem()
{
	//读取文件
	ReadFileToCouList("../DataSystem/Data/CourseTable.txt", &dataSystem.m_courseTable);
	ReadFileToOptCourseList("../DataSystem/Data/OptCourseTable.txt", &dataSystem.m_optCourseTable);
	ReadFileToStuList("../DataSystem/Data/StudentTable.txt", &dataSystem.m_studentTable);
}


