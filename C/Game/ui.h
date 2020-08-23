#ifndef UI_H
#define UI_H
#include <stdio.h>
#include <string.h>
#include <Windows.h>

extern HANDLE hstdout;
void PrintXY(short x, short y, const char* str);

void PrintIntroduction();

void PrintHelp();

void PrintBye();
#endif
