#include "OptCourse.h"
extern unsigned GetOptCourseRecords();
void ReadFileToOptCourseList(const char* path, OptCourse_list* optCourseList)
{

	FILE* file = fopen(path, "r");
	unsigned lines = 0;
	OptCourse temp = { 0 };
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
	optCourseList->clear(optCourseList);
	//判断文件有几行
	lines = GetOptCourseRecords();
	if (lines == 0)
	{
		fprintf(stderr, "No data!");
		error;
		free(temp.m_cId);
		temp.m_cId = NULL;
		return;
	}
	fgets(str, sizeof(str), file); //跳过标题
	while (index != lines)
	{
		fscanf(file, "%u%15s%lf",&temp.m_sId, temp.m_cId, &temp.m_score);
		optCourseList->push_back(optCourseList, &temp);
		++index;
	}
	fclose(file);
	free(temp.m_cId);
	temp.m_cId = NULL;
}

void WriteFileFromOptCourseList(const char* path, const OptCourse_list* optCourseList, const char* mode)
{
	FILE* file = fopen(path, mode);
	OptCourse_list_iterator it = NULL;
	if (NULL == file)
	{
		fprintf(stderr, "Can't open file!");
		error;
		return;
	}
	if (strcmp(mode, "w") == 0)
		//%20s    %15s    %10s    %20s    %s    
	//	fprintf(file, "%15s%15s%10s\n", "学号", "课程号", "分数");
	{
		fprintf(file, "%-15s%-15s%-10s\n", "学号", "课程号", "分数");
	}
	if (strcmp(mode, "at") == 0)
		; //特意空语句
	it = optCourseList->begin((OptCourse_list*)optCourseList);
	while (it != optCourseList->end((OptCourse_list*)optCourseList))
	{
	//	fprintf(file, "%15u%15s%5.2lf\n", it->m_sId, it->m_cId, it->m_score);
		fprintf(file, "%-15u%-15s%-5.2lf\n", it->m_sId, it->m_cId, it->m_score);
		it = optCourseList->next((OptCourse_list*)optCourseList, it);
	}
	fclose(file);
}

OptCourse_list_iterator CompareOpt(const OptCourse* data1, const OptCourse* data2)
{
	if (strcmp(data1->m_cId, data2->m_cId) == 0 && fabs(data1->m_score - data2->m_score) < 0.000001 && data1->m_sId == data2->m_sId)
		return (OptCourse_list_iterator)data1;
	else
		return NULL;
}
