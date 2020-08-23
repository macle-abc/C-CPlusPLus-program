#pragma once

#include "Course.h"
#include "Student.h"
#include "OptCourse.h"
#include "..//Lib/error.h"
#include <stdarg.h>

typedef struct DataSystem
{
	Course_list m_courseTable;
	Student_list m_studentTable;
	OptCourse_list m_optCourseTable;
}DataSystem;
typedef enum DataType
{
	student,
	course,
	optCourse,
}DataType;

//要储存的数据 判断条件 要判断的数据类型 数据 判断值
typedef void (*HelpSearchAndSavePointer)(DataSystem* data, bool(*ConditionSearch)(const void* data, const void* con), DataType dataType, const void* conArg1, const void* conArg2);

void InitDataSystem(DataSystem* dataSystem);
void ForeachDataSystemByCondition(const DataSystem * dataSystem, DataType dataType, HelpSearchAndSavePointer help, bool(*condition)(const void * data1, const void * data2), const void * conArg2, DataSystem* result);
void PrintfDataSystemToString(const DataSystem * dataSystem, mystring* text);
void ClearDataSystemMember(DataSystem* des, DataType dataType);
void CopyDataSystem(DataSystem* des, const DataSystem * src, DataType dataType);
void ClearDataSystem(DataSystem* des);
void DestroyDataSystemMember(DataSystem* des, DataType dataType);
void DestroyDataSystem(DataSystem* des);
void ReadFileToDataSystem();
