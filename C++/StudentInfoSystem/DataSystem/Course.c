#include "Course.h"

extern unsigned GetCourseRecords();
void ReadFileToCouList(const char* path, Course_list* couList)
{
	FILE* file = fopen(path, "r");
	unsigned lines = 0;
	Course temp = { 0 };
	char str[1024] = { 0 };
	unsigned index = 0;
	if (NULL == file)
	{
		fprintf(stderr, "Can't open file!");
		error;
		return;
	}
	temp.m_cId = malloc(1024);
	if (NULL == temp.m_cId)
	{
		fprintf(stderr, "Don't have enough memory");
		error;
		return;
	}
	memset(temp.m_cId, 0, 1024);
	temp.m_cName = malloc(1024);
	if (NULL == temp.m_cName)
	{
		fprintf(stderr, "Don't have enough memory");
		error;
		free(temp.m_cId);
		temp.m_cId = NULL;
		return;
	}
	memset(temp.m_cName, 0, 1024);
	temp.m_teacher = malloc(1024);
	if (NULL == temp.m_teacher)
	{
		fprintf(stderr, "Don't have enough memory");
		error;
		free(temp.m_cId);
		temp.m_cId = NULL;
		free(temp.m_cName);
		temp.m_cName = NULL;
		return;
	}
	couList->clear(couList);
	//判断文件有几行
	lines = GetCourseRecords();
	if (lines == 0)
	{
		fprintf(stderr, "No data!");
		error;
		free(temp.m_cId);
		temp.m_cId = NULL;
		free(temp.m_cName);
		temp.m_cName = NULL;
		free(temp.m_teacher);
		temp.m_teacher = NULL;
		return;
	}
	fgets(str, sizeof(str), file); //跳过标题
	while (index != lines)
	{
		fscanf(file, "%15s %15s %15s", temp.m_cId, temp.m_cName, temp.m_teacher);
		couList->push_back(couList, &temp);
		++index;
	}
	fclose(file);
	free(temp.m_cId);
	temp.m_cId = NULL;
	free(temp.m_cName);
	temp.m_cName = NULL;
	free(temp.m_teacher);
	temp.m_teacher = NULL;
}

void WriteFileFromCouList(const char* path, const Course_list* couList, const char* mode)
{
	FILE* file = fopen(path, mode);
	Course_list_iterator it = NULL;
	if (NULL == file)
	{
		fprintf(stderr, "Can't open file!");
		error;
		return;
	}
	if (strcmp(mode, "w") == 0)
		//%20s    %15s    %10s    %20s    %s    
	//	fprintf(file, "%15s%15s%15s\n", "课程号", "课程名", "教师名");
	{
		fprintf(file, "%-15s%-15s%-15s\n", "课程号", "课程名", "教师名");
	}
	if (strcmp(mode, "at") == 0)
		; //特意空语句
	it = couList->begin((Course_list*)couList);
	while (it != couList->end((Course_list*)couList))
	{
		//fprintf(file, "%15s%15s%15s\n", it->m_cId, it->m_cName, it->m_teacher);
		fprintf(file, "%-15s%-15s%-15s\n", it->m_cId, it->m_cName, it->m_teacher);
		it = couList->next((Course_list*)couList, it);
	}
	fclose(file);
}

Course* CompareCou(Course* data1, const Course* data2)
{
	if (strcmp(data1->m_cId, data2->m_cId) == 0 && strcmp(data1->m_cName, data2->m_cName) == 0 && strcmp(data1->m_teacher, data2->m_teacher) == 0)
		return data1;
	else
		return NULL;
}
