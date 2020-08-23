#pragma once
#include "Schedule.h"
#include <Windows.h>
#include <cstdio>
extern HANDLE hstdout;
void printXY(short x, short y, const string& str);
void ShowFunctionalArea(); //展示功能区
void ShowStatusBar(const Schedule& schedule); //展示状态栏
void ShowOptionArea(); //展示选项区
void ShowProcessStatusArea(const Schedule& schedule); //展示进程状态信息
void ShowInterface(const Schedule& schedule); //all
void ShowResource(const Schedule& schedule);
void Location(int x, int y);

