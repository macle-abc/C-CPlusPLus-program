#pragma once
#include "BitMap.h"
#include "Schedule.h"
#include "Show.h"
#include <ctime>
#include <string>
#include <Windows.h>
#include <cstdlib>
#include <iostream>
#include <regex>
#include <ctime>
#include <cstdarg>
#include <conio.h>

extern BitMap* bitMap;

using std::string;
using std::regex;
using std::cout;
using std::endl;
using std::cin;
using std::regex_match;
using std::cerr;

enum choose
{
	add = 1,
	kill,
	quit,
	other
};
Schedule& Init();
void Run(Schedule & schedule);
choose ProcessInteraction(Schedule& schedule);//返回值为处理结果
void SystemProcess(Schedule& schedule, choose which, ...);
