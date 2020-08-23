#include "Student.h"

void ReadFileToStuList(const char* path, Student_list* stuList)
{
	FILE* file = fopen(path, "r");
	unsigned lines = 0U;
	Student temp = { 0 };
	char str[1024] = { 0 };
	unsigned index = 0;

	if (NULL == file)
	{
		fprintf(stderr, "Can't open file!");
		error;
		return;
	}
	temp.m_major = malloc(20);
	if (NULL == temp.m_major)
	{
		fprintf(stderr, "Don't have enough memory!");
		error;
		return;
	}
	memset(temp.m_major, 0, 20);
	temp.m_name = malloc(20);
	if (NULL == temp.m_name)
	{
		fprintf(stderr, "Don't have enough memory!");
		error;
		free(temp.m_major);
		temp.m_major = NULL;
		return;
	}
	memset(temp.m_name, 0, 20);
	stuList->clear(stuList);
	//判断文件有几行
	lines = GetStudentRecords();
	if (0 == lines)
	{
		fprintf(stderr, "No data!");
		error;
		free(temp.m_major);
		temp.m_major = NULL;
		free(temp.m_name);
		temp.m_name = NULL;
		return;
	}
	fgets(str, sizeof(str), file); //跳过标题
	while (index != lines)
	{
		fscanf(file, "%20s %u %u %20s %c", temp.m_name, &temp.m_id, &temp.m_class, temp.m_major, &temp.m_sex);
		stuList->push_back(stuList, &temp);
		++index;
	}
	fclose(file);
	free(temp.m_major);
	free(temp.m_name);
	temp.m_major = NULL;
	temp.m_name = NULL;
}

void WriteFileFromStuList(const char* path, const Student_list* stuList, const char* mode)
{
	FILE* file = fopen(path, mode);
	Student_list_iterator it = NULL;
	if (NULL == file)
	{
		fprintf(stderr, "Can't open file!");
		error;
		return;
	}
	if (strcmp(mode, "w") == 0)
	{	//%20s    %15s    %10s    %20s    %s    
//		fprintf(file, "%20s%15s%15s%20s%15s\n", "姓名", "学号", "班级", "专业", "性别");
		fprintf(file, "%-20s%-15s%-15s%-20s%-15s\n", "姓名", "学号", "班级", "专业", "性别");
	}
	if (strcmp(mode, "at") == 0)
		; //特意空语句
	it = stuList->begin((Student_list*)stuList);
	while (it != stuList->end((Student_list*)stuList))
	{
	//	fprintf(file, "%20s%15u%10u%20s%5c\n", it->m_name, it->m_id, it->m_class, it->m_major, it->m_sex);
		fprintf(file, "%-20s%-15u%-10u%-20s%-5c\n", it->m_name, it->m_id, it->m_class, it->m_major, it->m_sex);
		it = stuList->next((Student_list*)stuList, it);
	}
	fclose(file);
}

Student_list_iterator CompareStu(Student * data1, const Student* data2)
{
	if (data1->m_class == data2->m_class && data1->m_id == data2->m_id && strcmp(data1->m_major, data2->m_major) == 0 \
			&& strcmp(data1->m_name, data2->m_name) == 0 && data1->m_sex == data2->m_sex)
		return data1;
	else
		return NULL;
}
