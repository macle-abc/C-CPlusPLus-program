#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <Windows.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ROWMAX 25	//最大行数
#define COLUMNMAX 40	//最大列数
#define INITSNAKENODENUM 4	//蛇初始化长度

	enum {rowBorder, columnBorder, map, snakeBody, snakeHead, food};

	typedef int Map[ROWMAX][COLUMNMAX];
	typedef struct Snake
	{
		int x;
		int y;
		char direction;
		struct Snake * next;
	}Snake;
	typedef struct Food
	{
		int x;
		int y;
	}Food;
	typedef struct UserInfo
	{
		unsigned score;
		char name[80];
		struct UserInfo * next;
	}UserInfo;
	typedef const char * FilePath;
	typedef int rank;

	//初始化游戏地图
	void initGameMap(Map m);
	
	//将蛇的位置填入地图中
	void addSnakeToMap(Map m, Snake * SnakeHeader);

	//打印游戏
	void printGame(Map m);

	//出现食物
	void produceFood(Snake * SnakeHeader, Map m, Food * f);

	//游戏流程
	void gameFlow(void);

	//吃到食物
	bool eatFood(Snake * SnakeHeader, Map m, Food * f);

	//清除蛇的位置
	void clearSnake(Snake * SnakeHeader, Map m);
	
	//吃了自己
	bool SnakeEatItself(Snake * SnakeHeader);

	//检查蛇是否越界
	bool SnakeOverStep(Snake * SnakeHeader);

	//检查点是否越界
	bool pointOverstep(int x, int y);

	//添加蛇身
	void addSnakeBody(Snake * SnakeHeader);
	
	//能否移动蛇头
	bool moveHead(Snake * SnakeHeader);

	//移动蛇身
	void moveBody(Snake * SnakeBody);

	//移动函数
	void move(Snake * SnakeHeader);

	//初始化蛇
	Snake * initSnake(void);

	//释放内存
	void freeSnake(Snake ** SnakeHeader);
	void freeUserInfo(UserInfo ** UserHeader);

	//光标函数
	void HideCursor();
	void gotoxy(int x, int y);
	
	//储存用户游戏信息
	FilePath saveUserInfo(UserInfo * user);

	//读取用户游戏信息
	void loadUserInof(FilePath filePath, UserInfo ** userLinkList);

	//排序
	UserInfo * Sort(UserInfo * Header);
	
	//查找名次
	rank findByName(UserInfo * Header, char name[80]);

	//打印排行榜
	void printfRank(UserInfo * Header);

#ifdef __cplusplus
}
#endif