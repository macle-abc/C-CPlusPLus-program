#include "SearchAssistance.h"

DataSystem searchResult;
extern DataSystem dataSystem;

bool FuzzySearch(const char* des, const char* src)
{
	char* res = memchr(src, des[0], strlen(src));  //根据要查找的字符串第一个字符，切割源字符串
	int n = 0;
	if (res == NULL)
	{
		fprintf(stderr, "No find!");
		error;
		return 0;
	}

	while (1)
	{
		n = memcmp(res, des, strlen(des) - 1); //比较
		if (n != 0)
		{
			if (strlen(res) <= strlen(des))  //切割出的字符串小于要查找字符串的长度
			{
				return 0;
			}
			else
			{
				//根据要查找的第一个字符继续切割
				res = memchr(res + 1, des[0], strlen(res));
				if (res == NULL)
				{
					return 0;
				}

			}
		}
		else
		{ //如果n = 0，找到
			return 1;
		}
	}
}

//要储存的数据 判断条件 要判断的数据类型 数据 判断值
//typedef void (*HelpSearchAndSavePointer)(DataSystem* data, bool(*ConditionSearch)(void* data, void* con), DataType dataType, void* conArg1, void* conArg2);

static void HelpPointer(DataSystem* data, ConditionSearch condition, DataType dataType, const void* conArg1, const void* conArg2)
{
//	help(dataSystem, condition, student, sit, conArg2);
	if (dataType == student)
	{
		if (condition(conArg1, conArg2))
			data->m_studentTable.push_back(&data->m_studentTable, (const Student*)conArg1);
	}
	if (dataType == course)
	{
		if (condition(conArg1, conArg2))
			data->m_courseTable.push_back(&data->m_courseTable, (const Course*)conArg1);
	}
	if (dataType == optCourse)
	{
		if (condition(conArg1, conArg2))
			data->m_optCourseTable.push_back(&data->m_optCourseTable, (const OptCourse*)conArg1);
	}
}
void FindAndSave(ConditionSearch condition, DataType dataType, const void* conVal)
{	
	InitDataSystem(&searchResult);
	if (dataType == student)
	{
		ForeachDataSystemByCondition(&dataSystem, student, HelpPointer, condition, conVal, &searchResult);
	}
	if (dataType == course)
	{
		ForeachDataSystemByCondition(&dataSystem, course, HelpPointer, condition, conVal, &searchResult);
	}
	if (dataType == optCourse)
	{
		ForeachDataSystemByCondition(&dataSystem, optCourse, HelpPointer, condition, conVal, &searchResult);
	}
}
void CollectData()
{
	dataSystem.m_courseTable.clear(&dataSystem.m_courseTable);
	dataSystem.m_optCourseTable.clear(&dataSystem.m_optCourseTable);
	dataSystem.m_studentTable.clear(&dataSystem.m_studentTable);
	ReadFileToCouList("../DataSystem/Data/CourseTable.txt", &dataSystem.m_courseTable);
	ReadFileToOptCourseList("../DataSystem/Data/OptCourseTable.txt", &dataSystem.m_optCourseTable);
	ReadFileToStuList("../DataSystem/Data/StudentTable.txt", &dataSystem.m_studentTable);
}

bool SearchStudentByName(const void* data, const void * conVal)
{
	const Student* tempData = NULL;
	const char* tempCon = NULL;
	if (NULL == data || NULL == conVal)
		return FALSE;
	tempData = (const Student*)data;
	tempCon = (const char*)conVal;
	if (FuzzySearch(tempCon, tempData->m_name))
		return TRUE;
	else
		return FALSE;
}

bool SearchStudentById(const void* data, const void * conVal)
{
	const Student* tempData = NULL;
	const unsigned* tempCon = NULL;
	if (NULL == data || NULL == conVal)
		return FALSE;
	tempData = (const Student*)data;
	tempCon = (const unsigned*)conVal;
	if (tempData->m_id == *tempCon)
		return TRUE;
	else
		return FALSE;
}

bool SearchStudentByClass(const void* data, const void* conVal)
{

	const Student* tempData = NULL;
	const unsigned* tempCon = NULL;
	if (NULL == data || NULL == conVal)
		return FALSE;
	tempData = (const Student*)data;
	tempCon = (const unsigned*)conVal;
	if (tempData->m_class == *tempCon)
		return TRUE;
	else
		return FALSE;
}

bool SearchStudentByMajor(const void* data, const void* conVal)
{

	const Student* tempData = NULL;
	const char* tempCon = NULL;
	if (NULL == data || NULL == conVal)
		return FALSE;
	tempData = (const Student*)data;
	tempCon = (const char*)conVal;
	if (FuzzySearch(tempCon, tempData->m_major))
		return TRUE;
	else
		return FALSE;
}

bool SearchCoureById(const void* data, const void* conVal)
{
	const Course* tempData = NULL;
	const char* tempCon = NULL;
	if (NULL == data || NULL == conVal)
		return FALSE;
	tempData = (const Course*)data;
	tempCon = (const char*)conVal;
	if (FuzzySearch(tempCon, tempData->m_cId))
		return TRUE;
	else
		return FALSE;
}

bool SearchCourseByName(const void* data, const void* conVal)
{
	const Course* tempData = NULL;
	const char* tempCon = NULL;
	if (NULL == data || NULL == conVal)
		return FALSE;
	tempData = (const Course*)data;
	tempCon = (const char*)conVal;
	if (FuzzySearch(tempCon,tempData->m_cName))
		return TRUE;
	else
		return FALSE;
}

bool SearchCourseByTeacher(const void* data, const void* conVal)
{
	const Course* tempData = NULL;
	const char* tempCon = NULL;
	if (NULL == data || NULL == conVal)
		return FALSE;
	tempData = (const Course*)data;
	tempCon = (const char*)conVal;
	if (FuzzySearch(tempCon, tempData->m_teacher))
		return TRUE;
	else
		return FALSE;
}

bool SearchOptCorseByStudentId(const void* data, const void* conVal)
{
	const OptCourse* tempData = NULL;
	const unsigned* tempCon = NULL;
	if (NULL == tempData || NULL == tempCon)
	{
		return FALSE;
	}
	tempData = (const OptCourse*)data;
	tempCon = (const unsigned*)conVal;
	if (tempData->m_sId == *tempCon)
		return TRUE;
	else
		return FALSE;
}

bool SearchOptCourseByCourseId(const void* data, const void* conVal)
{
	const OptCourse* tempData = NULL;
	const char* tempCon = NULL;
	if (NULL == tempData || NULL == tempCon)
	{
		return FALSE;
	}
	tempData = (const OptCourse*)data;
	tempCon = (const char*)conVal;
	if (FuzzySearch(tempCon, tempData->m_cId))
		return TRUE;
	else
		return FALSE;
}

bool SearchOptCourseByScore(const void* data, const void* conVal)
{
	const OptCourse* tempData = NULL;
	const double* tempCon = NULL;
	if (NULL == tempData || NULL == tempCon)
	{
		return FALSE;
	}
	tempData = (const OptCourse*)data;
	tempCon = (const double*)conVal;
	if (fabs(tempData->m_score - *tempCon) < 0.000001)
		return TRUE;
	else
		return FALSE;
}
