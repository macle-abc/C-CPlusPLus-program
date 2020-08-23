#include <stdio.h>
#include <time.h>
#include "head_game.h"


int main(void)
{
	unsigned int game2048[N][N], copy[N][N];//game2048[N][N]表示游戏数据,copy[N][N]表示游戏上一步数据
	unsigned int low, column, sum, return_number;//sum表示copy[N][N]与game2048[N][N]相同数据的个数,return_number用于储存int check(int[][N])函数的返回值
    long double game_score = 0.0, sum_score = 0.0;//game_score代表每次数据叠加时的游戏分数,sum_score代表游戏总分
	long double * score = &game_score, *p_sum_score = &sum_score;//指针score指向game_score，指针p_sum_score指向sum_score
	char chose;//储存用户的操作
	void(*p)(unsigned int[][N], long double *, long double *) = NULL;
	
	srand((unsigned int)time(NULL));//设定随机数种子
	//初始每个数据为'.'
	for (low = 0; low < N; low++)
		for (column = 0; column < N; column++)
			copy[low][column] = game2048[low][column] = '.';
	printf("      *************************\n        欢迎来到2048小游戏\n      *************************\n\n\n");
	show(game2048);//展示初始化结果
	printf("请输入S或s表示游戏开始\n");
	chose = getch();
	while (chose != 's' && chose != 'S')
	{
		printf("输入错误,是否继续游戏（S或s继续，其他输入则结束游戏)\n");
		chose = getch();
		if (chose != 's' && chose != 'S')
			return 0;
	}
	game_rand(game2048);//随机出现数据
	show(game2048);
	//游戏进程
	while (1)
	{
		sum = 0;
		return_number = check(game2048);
		if (return_number)//判断游戏是否结束
		{
			//复制上一步游戏数据
			for (low = 0; low < N; low++)
				for (column = 0; column < N; column++)
					copy[low][column] = game2048[low][column];
			printf("请输入w s a d q或W S A D Q（w或W表示上移,s或S表示下移，a或A表示左移，d或D表示右移，q或Q表示退出游戏)\n");
			chose = getch();//用户输入
			while (chose != 'w' && chose != 'W' && chose != 's' && chose != 'S' && chose != 'a' && chose != 'A' && chose != 'd' && chose != 'D')
			{
				if ('q' == chose || 'Q' == chose)
					return 0;
				else
				{
					printf("请输入错误，请重新输入\n");
					chose = getch();
				}
			}
			if ('w' == chose || 'W' == chose)//输入上
				p = move_up;
			else if ('s' == chose || 'S' == chose)//输入下
				p = move_down;
			else if ('a' == chose || 'A' == chose)//输入左
				p = move_left;
			else if ('d' == chose || 'D' == chose)//输入右
				p = move_right;
			(*p)(game2048, score, p_sum_score);//开始移动
											   //判断该方向上能否继续移动
			for (low = 0; low < N; low++)
				for (column = 0; column < N; column++)
					if (copy[low][column] == game2048[low][column])//上一步数据与游戏新数据相同
						sum++;
			if (sum != N * N)//若存在数据不相同则出现随机数
				game_rand(game2048);
			show(game2048);
			printf("分数为：%.lf\n\n\n", *p_sum_score);
		}
		else
		{
			printf("游戏结束.\n");
			system("pause");
			return 0;
		}

	}
	return 0;
}
