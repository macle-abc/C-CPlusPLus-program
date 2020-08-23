#include "CourseAssistance.h"

extern DataSystem dataSystem;
int AddCourseRecord(const Course* data)
{
	return dataSystem.m_courseTable.push_back(&dataSystem.m_courseTable, data);
}


static struct Remove
{
	ConditionCou pFun;
	const void* arg;
}helpRm;

static int RemoveIf(const Course* data)
{
	if (helpRm.pFun(data, helpRm.arg))
		return TRUE;
	else
		return FALSE;
}

int RemoveCourseRecord(ConditionCou condition, const void * con)
{
	helpRm.pFun = condition;
	helpRm.arg = con;
	return dataSystem.m_courseTable.remove_if(&dataSystem.m_courseTable, RemoveIf);
}


static struct ModifyOptCourse
{
	ConditionCou pFun;
	const void* arg;
}helpMvOp;

static int ModifyIfOptCourse(const OptCourse* data)
{
	if (helpMvOp.pFun(data, helpMvOp.arg))
		return TRUE;
	else
		return FALSE;
}

int SetScore(ConditionCou condition, const void * con, OptCourse* data)
{
	OptCourse_list* result = NULL;
	OptCourse_list_iterator it = NULL;
	OptCourse_list_iterator current = NULL;
	OptCourse_list_iterator next = NULL;
	OptCourse_list_iterator temp = NULL;
	helpMvOp.pFun = condition;
	helpMvOp.arg = con;
	result = dataSystem.m_optCourseTable.find_if(&dataSystem.m_optCourseTable, ModifyIfOptCourse);
	if (result->size(result) == 0)
	{
		fprintf(stderr, "No data!");
		error;
		return 0;
	}
	else
	{
		it = result->begin(result);
		while (it != result->end(result))
		{
			next = dataSystem.m_optCourseTable.begin(&dataSystem.m_optCourseTable);
			while (next != dataSystem.m_optCourseTable.end(&dataSystem.m_optCourseTable))
			{
				if (temp = CompareOpt(next, it))
				{
					current = temp;
					next = dataSystem.m_optCourseTable.next(&dataSystem.m_optCourseTable, current);
					break;
				}
				next = dataSystem.m_optCourseTable.next(&dataSystem.m_optCourseTable, next);
			}
			dataSystem.m_optCourseTable.erase(&dataSystem.m_optCourseTable, current);
			dataSystem.m_optCourseTable.insert(&dataSystem.m_optCourseTable, next, data);
			it = result->next(result, it);
		}
	}
	return 1;
}

static struct Modify
{
	ConditionCou pFun;
	const void* arg;
}helpMv;

static int ModifyIf(const Course* data)
{
	if (helpMv.pFun(data, helpMv.arg))
		return TRUE;
	else
		return FALSE;
}

int ModifyCoruseRecord(ConditionCou condition, const void * con, Course* data)
{
	Course_list* result = NULL;
	Course_list_iterator it = NULL;
	Course_list_iterator current = NULL;
	Course_list_iterator next = NULL;
	Course_list_iterator temp = NULL;
	helpMv.pFun = condition;
	helpMv.arg = con;
	result = dataSystem.m_courseTable.find_if(&dataSystem.m_courseTable, ModifyIf);
	if (result->size(result) == 0)
	{
		fprintf(stderr, "No data!");
		error;
		return 0;
	}
	else
	{
		it = result->begin(result);
		while (it != result->end(result))
		{
			next = dataSystem.m_courseTable.begin(&dataSystem.m_courseTable);
			while (next != dataSystem.m_courseTable.end(&dataSystem.m_courseTable))
			{
				if (temp = CompareCou(next, it))
				{
					current = temp;
					next = dataSystem.m_courseTable.next(&dataSystem.m_courseTable, current);
					break;
				}
				next = dataSystem.m_courseTable.next(&dataSystem.m_courseTable, next);
			}
			dataSystem.m_courseTable.erase(&dataSystem.m_courseTable, current);
			dataSystem.m_courseTable.insert(&dataSystem.m_courseTable, next, data);
			it = result->next(result, it);
		}
	}
	return 1;
}


bool RemoveCourseByCId(const void * data1, const void * data2)
{
	const Course* cou = NULL;
	const char* cid = NULL;
	if (NULL == data1 || NULL == data2)
		return FALSE;
	cou = (const Course*)data1;
	cid = (const char*)data2;
	if (strcmp(cou->m_cId, cid) == 0)
		return TRUE;
	else
		return FALSE;
}

bool RemoveCourseByTeacher(const void * data1, const void * data2)
{
	const Course* cou = NULL;
	const char* tea = NULL;
	if (NULL == data1 || NULL == data2)
		return FALSE;
	cou = (const Course*)data1;
	tea = (const char*)data2;
	if (strcmp(cou->m_teacher, tea) == 0)
		return TRUE;
	else
		return FALSE;
}

bool RemoveCourseByName(const void * data1, const void * data2)
{
	const Course* cou = NULL;
	const char* name = NULL;
	if (NULL == data1 || NULL == data2)
		return FALSE;
	cou = (const Course*)data1;
	name = (const char*)data2;
	if (strcmp(cou->m_cName, name) == 0)
		return TRUE;
	else
		return FALSE;
}

bool ModifyCourseById(const void * data1, const void * data2)
{
	const Course* cou1 = NULL;
	const char* cou2 = NULL;
	if (NULL == data1 || NULL == data2)
		return FALSE;
	cou1 = (const Course*)data1;
	cou2 = (const char*)data2;
	if (strcmp(cou1->m_cId, cou2) == 0)
		return TRUE;
	else
		return FALSE;
}

bool ModifyOptCourse(const void * data1, const void * data2)
{
	const OptCourse* opt1 = NULL;
	const OptCourse* opt2 = NULL;
	if (NULL == data1 || NULL == data2)
		return FALSE;
	opt1 = (const OptCourse*)data1;
	opt2 = (const OptCourse*)data2;
	if (strcmp(opt1->m_cId, opt2->m_cId) == 0 &&  opt1->m_sId == opt2->m_sId)
		return TRUE;
	else
		return FALSE;
}
