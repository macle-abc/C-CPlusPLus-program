#pragma once

#include <string.h>
#include "genlib.h"
#include "..//Lib/error.h"
#include "..//DataSystem/DataSystem.h"
extern DataSystem dataSystem;

typedef bool (*Compare)(const void* data1, const void* data2);
void Sort(Compare compare, DataType dataTpe);//排序至dataSystem,条件和类型需对应
void SaveResult(DataType dataTpe);
void OutputResult(const char* filePath, DataType dataTpe);
bool CompareByStudentID(const void * data1, const void * data2);
bool CompareByStudentName(const void * data1, const void * data2);
bool CompareByScore(const void * data1, const void * data2);
