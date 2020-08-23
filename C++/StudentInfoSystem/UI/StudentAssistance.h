#pragma once

#include "genlib.h"
#include "../DataSystem/Student.h"
#include "..//DataSystem/DataSystem.h"
#include "..//UI/SearchAssistance.h"
#include <math.h>

typedef bool (*ConditionStu)(const void* data1,const void* data2);
void AddStudentRecord(const Student* data);//使用前确保dataSystem全局变量得到初始化
int RemoveStudentRecord(ConditionStu condition, const void * con); //con必须为变量的地址, dataSystem全局变量需要得到初始化
int ModifyStudentRecord(ConditionStu condition, const void * con, Student* data);//con为变量地址 dataSystem需要初始化
int AddOptCourseRecord(unsigned stuId, string courseId,double score);//dataSystem需要初始化
bool RemoveStudentById(const void * data1, const void * data2);
bool RemoveStudentByName(const void * data1, const void * data2);
bool ModifyStudentById(const void * data1, const void * data2);

