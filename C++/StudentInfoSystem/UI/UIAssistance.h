#pragma once

#include <stdio.h>
#include "genlib.h"
#include "..//Lib/String/__string.h"
#include "..//UI/FileUI.h"

char* GetOpenFilePath();
char* GetSaveFilePath();
void ReadFileToEditor(const char* filePath, mystring* textData, Editor* editor);
void WriteFileFromFileUI(const char* filePath);
unsigned GetStudentRecords();
unsigned GetCourseRecords();
unsigned GetOptCourseRecords();
unsigned GetFileLines(const char* path);