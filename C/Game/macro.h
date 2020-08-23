#ifndef MACRO_H_
#define MACRO_H_

//用于本项目中使用的宏
#include <Windows.h>
#include <stdio.h>
#define PrintError(str) fprintf(stderr, "%s", str);
#include <time.h>

#define MYRAND ((double)(clock() % 1000) / 1000)

//以下用于设置文本颜色
#define SET_CYAN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE)
#define SET_WHITE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN | FOREGROUND_BLUE)
#define SET_RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED)
#define SET_GREEN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN)
#define SET_YELLOW SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN)


//英雄的防御能力会降低受到的伤害率。
//此值不应太大
#define C_IMMUNE 24.0

//用于计算暴击几率。 此值不应太大。
#define C_CRIT_MONEY 40.0

//出售装备时，获得原始价格的比率。
#define C_SELL 0.6

//当对敌人造成一定程度的伤害时，会根据此伤害率收到金钱奖励
#define C_RECEIVE 5

//暴击系数
#define C_CRIT 1.5



#endif