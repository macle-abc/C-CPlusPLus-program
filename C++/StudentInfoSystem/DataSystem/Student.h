#pragma once

#include "genlib.h"
#include "..//UI/UIAssistance.h"
#include "..//Lib/error.h"
#include <string.h>
typedef struct Student
{
	unsigned int m_id;//学号
	string m_name;//姓名
	unsigned int m_class;//班级
	string m_major;//专业
	char m_sex;//性别
}Student;

//#include <stdio.h>
#define __list_t Student
#include "list.h"

void CopyStu(Student* des, const Student* src);
void DestructStu(Student* stu);

void ReadFileToStuList(const char* path, Student_list* stuList);
void WriteFileFromStuList(const char* path, const Student_list* stuList, const char* mode);

Student_list_iterator CompareStu(Student * data1, const Student* data2);

