#pragma once

#include "genlib.h"
#include "..//Lib/error.h"
#include <stdio.h>
#include <string.h>
typedef struct Couse
{
	string m_cId;//课程号
	string m_cName;//课程名
	string m_teacher;//教师名
}Course;


//#include <stdio.h>
#define __list_t  Course
#include "list.h"

void DestructCourse(Course* cou);
void CopyCourse(Course* des, const Course* src);
void ReadFileToCouList(const char* path, Course_list* courseList);
void WriteFileFromCouList(const char* path, const Course_list* courseList, const char* mode);
Course* CompareCou(Course* data1, const Course* data2);
