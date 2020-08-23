#pragma once

#include "genlib.h"
#include "..//DataSystem/Course.h"
#include "..//DataSystem/DataSystem.h"
#include "..//Lib/check.h"
#include "..//Lib/error.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

typedef bool (*ConditionCou)(const void* data1, const void* data2);
int AddCourseRecord(const Course* data);
int RemoveCourseRecord(ConditionCou condition, const void * con);
int ModifyCoruseRecord(ConditionCou condition, const void * con, Course* data);
int SetScore(ConditionCou conditio, const void * con, OptCourse* data);

bool RemoveCourseByCId(const void * data1, const void * data2);
bool RemoveCourseByTeacher(const void * data1, const void * data2);
bool RemoveCourseByName(const void * data1, const void * data2);
bool ModifyCourseById(const void * data1, const void * data2);
bool ModifyOptCourse(const void * data1, const void * data2);
