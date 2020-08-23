#include "SortAssistance.h"

//1小于2的时候为真
bool CompareByStudentID(const void * data1, const void * data2)
{
	const Student* temp1 = NULL;
	const Student* temp2 = NULL;
	if (NULL == data1 || NULL == data2)
		return FALSE;
	temp1 = (const Student*)data1;
	temp2 = (const Student*)data2;
	if (temp1->m_id < temp2->m_id)
		return TRUE;
	else
		return FALSE;
}

bool CompareByStudentName(const void * data1, const void * data2)
{
	const Student* temp1 = NULL;
	const Student* temp2 = NULL;
	if (NULL == data1 || NULL == data2)
		return FALSE;
	temp1 = (const Student*)data1;
	temp2 = (const Student*)data2;
	if (strcmp(temp1->m_name, temp2->m_name) < 0)
		return TRUE;
	else
		return FALSE;
}

bool CompareByScore(const void * data1, const void * data2)
{
	const OptCourse* temp1 = NULL;
	const OptCourse* temp2 = NULL;
	if (NULL == data1 || NULL == data2)
		return FALSE;
	temp1 = (const OptCourse*)data1;
	temp2 = (const OptCourse*)data2;
	if (temp1->m_score < temp2->m_score)
		return TRUE;
	else
		return FALSE;

}

static Compare __void_cmp;

static int
student_cmp(const Student* s1, const Student* s2)
{
	return __void_cmp(s1, s2);
}

static int
course_cmp(const Course* c1, const Course* c2)
{
	return __void_cmp(c1, c2);
}

static int
optcourse_cmp(const OptCourse* o1, const OptCourse* o2)
{
	return __void_cmp(o1, o2);
}

void Sort(Compare compare, DataType dataType)
{
	__void_cmp = compare;

	if (dataType == student)
	{
		dataSystem.m_studentTable.sort(&dataSystem.m_studentTable, student_cmp);
	}
	if (dataType == course)
	{
		dataSystem.m_courseTable.sort(&dataSystem.m_courseTable, course_cmp);
	}
	if (dataType == optCourse)
	{
		dataSystem.m_optCourseTable.sort(&dataSystem.m_optCourseTable, optcourse_cmp);
	}
}

void SaveResult(DataType dataType)
{
	if (dataType == student)
	{
		WriteFileFromStuList("../DataSystem/Data/StudentTable.txt", &dataSystem.m_studentTable, "w");
	}
	if (dataType == course)
	{
		WriteFileFromCouList("../DataSystem/Data/CourseTable.txt", &dataSystem.m_courseTable, "w");
	}
	if (dataType == optCourse)
	{
		WriteFileFromOptCourseList("../DataSystem/Data/OptCourseTable.txt", &dataSystem.m_optCourseTable, "w");
	}
}

void OutputResult(const char* filePath, DataType dataType)
{
	if (dataType == student)
	{
		WriteFileFromStuList(filePath, &dataSystem.m_studentTable, "w");
	}
	if (dataType == course)
	{
		WriteFileFromCouList(filePath, &dataSystem.m_courseTable, "w");
	}
	if (dataType == optCourse)
	{
		WriteFileFromOptCourseList(filePath, &dataSystem.m_optCourseTable, "w");
	}
}
