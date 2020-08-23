#include "StudentAssistance.h"

static DataSystem tempSystem;
extern DataSystem dataSystem;
void AddStudentRecord(const Student* data)
{
	dataSystem.m_studentTable.push_back(&dataSystem.m_studentTable, data);
}

static struct Remove
{
	ConditionStu pFun;
	const void* arg;
}helpRm;

static int RemoveIf(const Student* data)
{
	if (helpRm.pFun(data, helpRm.arg))
		return TRUE;
	else
		return FALSE;
}

int RemoveStudentRecord(ConditionStu condition, const void * con)
{
	helpRm.pFun = condition;
	helpRm.arg = con;
	return dataSystem.m_studentTable.remove_if(&dataSystem.m_studentTable, RemoveIf);
}


static struct Modify
{
	ConditionStu pFun;
	const void* arg;
}helpMv;

static int mvIf(const Student* data)
{
	if (helpMv.pFun(data, helpMv.arg))
		return TRUE;
	else
		return FALSE;
}

int ModifyStudentRecord(ConditionStu condition, const void * con, Student* data)
{
	Student_list* result = NULL;
	Student_list_iterator it = NULL;
	Student_list_iterator current = NULL;
	Student_list_iterator next = NULL;
	Student_list_iterator temp = NULL;
	helpMv.pFun = condition;
	helpMv.arg = con;
	result = dataSystem.m_studentTable.find_if(&dataSystem.m_studentTable, mvIf);
	if (result->size(result) == 0)
	{
		return 0;
	}
	else
	{
		it = result->begin(result);
		while (it != result->end(result))
		{
			next = dataSystem.m_studentTable.begin(&dataSystem.m_studentTable);
			while (next != dataSystem.m_studentTable.end(&dataSystem.m_studentTable))
			{
				if (temp = CompareStu(next, it))
				{
					current = temp;
					next = dataSystem.m_studentTable.next(&dataSystem.m_studentTable, current);
					break;
				}
				next = dataSystem.m_studentTable.next(&dataSystem.m_studentTable, next);
			}
			dataSystem.m_studentTable.erase(&dataSystem.m_studentTable, current);
			dataSystem.m_studentTable.insert(&dataSystem.m_studentTable, next, data);
			it = result->next(result, it);
		}
	}
	return 1;
}

int AddOptCourseRecord(unsigned stuId, string courseId, double score)
{
	OptCourse temp = { 0 };
	temp.m_cId = malloc(strlen(courseId) + 1);
	strcpy(temp.m_cId, courseId);
	temp.m_sId = stuId;
	temp.m_score = score;
	return dataSystem.m_optCourseTable.push_back(&dataSystem.m_optCourseTable, &temp);
}

bool RemoveStudentById(const void * data1, const void * data2)
{
	Student* stu = NULL;
	const unsigned* id = NULL;
	if (NULL == data1 || NULL == data2)
		return FALSE;
	stu = (Student*)data1;
	id = (const unsigned*)data2;
	if (stu->m_id == *id)
		return TRUE;
	else
		return FALSE;
}

bool RemoveStudentByName(const void * data1, const void * data2)
{
	Student* stu = NULL;
	const char* name = NULL;
	if (NULL == data1 || NULL == data2)
		return FALSE;
	stu = (Student*)data1;
	name = (const char*)data2;
	if (strcmp(stu->m_name,name) == 0)
		return TRUE;
	else
		return FALSE;
}

bool ModifyStudentById(const void * data1, const void * data2)
{
	Student* stu1 = NULL;
	const unsigned* id = NULL;
	if (NULL == data1 || NULL == data2)
		return FALSE;
	stu1 = (Student*)data1;
	id = (const unsigned *)data2;
	if (stu1->m_id == *id)
		return TRUE;
	else
		return FALSE;
}
