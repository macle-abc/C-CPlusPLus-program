#pragma once

#include "genlib.h"
#include "..//Lib/error.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

typedef struct OptCourse
{
	unsigned int m_sId;//学号
	string m_cId;//课程号
	double m_score;//该科成绩
}OptCourse;

//#include <stdio.h>
#define __list_t OptCourse
#include "list.h"


void CopyOpt(OptCourse* des, const OptCourse* src);
void DestructOpt(OptCourse* opt);
void ReadFileToOptCourseList(const char* path, OptCourse_list* optCourseList);
void WriteFileFromOptCourseList(const char* path, const OptCourse_list* optCourseList, const char* mode);
OptCourse_list_iterator CompareOpt(const OptCourse* data1, const OptCourse* data2);

