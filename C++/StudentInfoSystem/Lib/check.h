#pragma once

#include <stdio.h>
#include <Windows.h>
#define ClearIn()	while (fgetc(stdin) != '\n') {}

// this file should be included
#include <ctype.h>

#define CHECK_AND_PROMPT(message, checkData, formate) do\
							{\
								if (!check(checkData, formate)) \
								{	\
									MessageBox(NULL, message, " ‰»Î¥ÌŒÛ", MB_ICONHAND); \
									return; \
								}	\
							}while (0)
// 8 9 8/9 digits
// 10 <=10 chars
// 7 double
// 1 M/W
int check(const char* text, int fmt);
