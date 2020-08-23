#include "head_game.h"
void show(unsigned int game[][N])
{
	int low, column;

	for (low = 0; low < N; low++)
	{
		for (column = 0; column < N; column++)
			if (game[low][column] != '.')//数据已更改则打印新数据
				printf("%9u", game[low][column]);
			else//数据未更改则打印'.'
				printf("%9c", game[low][column]);
		printf("\n\n");
	}
}
void game_rand(unsigned int game[][N])
{
	int low_rand, column_rand, result_rand;//low_rand行数随机，column_rand列数随机，result_rand数据随机

	while (1)
	{
		result_rand = (rand() % 4)> 2 ? 4 : 2;//设置出现2的几率为4的三倍
		low_rand = rand() % 4;//行数随机
		column_rand = rand() % 4;//列数随机
		if ('.' == game[low_rand][column_rand])//数据未被更改仍为初始值.
		{
			game[low_rand][column_rand] = result_rand;//将出现的2或4随机赋值给4*4的数组元素
			break;
		}
	}
}
int check(unsigned int game[][N])
{
	int low, column;
	for (low = 0; low < N; low++)
		for (column = 0; column < N; column++)
			if (game[low][column] == '.')//数据仍为初始值.则继续游戏
				return 1;
			else
			{
				if (low == 0 && column == 0)//左上角数据
					if (game[low][column] == game[low][column + 1] || game[low][column] == game[low + 1][column])//相邻之间数据存在相同则继续游戏
						return 1;
				if (low == 0 && column == N - 1)//右上角数据
					if (game[low][column] == game[low][column - 1] || game[low][column] == game[low + 1][column])//相邻之间数据存在相同则继续游戏
						return 1;
				if (low == N - 1 && column == 0)//左下角数据
					if (game[low][column] == game[low - 1][column] || game[low][column] == game[low][column + 1])//相邻之间数据存在相同则继续游戏
						return 1;
				if (low == N - 1 && column == N - 1)//右下角数据
					if (game[low][column] == game[low - 1][column] || game[low][column] == game[low][column - 1])//相邻之间数据存在相同则继续游戏
						return 1;
				if (low == 0 && (column != 0 && column != N - 1))//第一行数据
					if (game[low][column] == game[low][column - 1] || game[low][column] == game[low][column + 1] || game[low][column] == game[low + 1][column])//相邻之间数据存在相同则继续游戏
						return 1;
				if (low == N - 1 && (column != 0 && column != N - 1))//最后一行数据
					if (game[low][column] == game[low][column - 1] || game[low][column] == game[low][column + 1] || game[low][column] == game[low - 1][column])//相邻之间数据存在相同则继续游戏
						return 1;
				if ((low != 0 && low != N - 1) && column == 0)//第一列数据
					if (game[low][column] == game[low + 1][column] || game[low][column] == game[low - 1][column] || game[low][column] == game[low][column + 1])//相邻之间数据存在相同则继续游戏
						return 1;
				if ((low != 0 && low != N - 1) && column == N - 1)//最后一列数据
					if (game[low][column] == game[low + 1][column] || game[low][column] == game[low - 1][column] || game[low][column] == game[low][column - 1])//相邻之间数据存在相同则继续游戏
						return 1;
				if (low != 0 && low != N - 1 && column != 0 && column != N - 1)//中间数据
					if (game[low][column] == game[low + 1][column] || game[low][column] == game[low - 1][column] || game[low][column] == game[low][column - 1] || game[low][column] == game[low][column + 1])//相邻之间数据存在相同则继续游戏
						return 1;
			}
	return 0;//历遍数组元素仍为返回1则说明游戏结束
}
void move_up(unsigned int game[][N], long double * p, long double * s)
{
	int low, column, low_new;//low与column为原始数据的行列，low_new为新数据行

	for (column = 0; column < N; column++)
		for (low = 0; low < N - 1; low++)
			if ('.' == game[low][column])//原始数据未变化
			{
				for (low_new = low + 1; low_new < N; low_new++)
				{
					if (game[low_new][column] != '.')//新数据已经变化
					{
						//将新数据代替原始数据
						game[low][column] = game[low_new][column];
						game[low_new][column] = '.';
						break;//结束循环
					}
				}
			}
			else	//原始数据已经变化不为'.'
			{
				for (low_new = low + 1; low_new < N; low_new++)
					if (game[low_new][column] != '.')//新数据已经变化
					{
						if (game[low][column] == game[low_new][column])//数据可累加情况
						{
							game[low][column] += game[low][column];
							game[low_new][column] = '.';
							*p = (double)game[low][column];
							*s = *s + *p;
						}
						else//数据不可累加情况
						{
							if (low_new - low != 1)//新数据与原数据间隔不为1时发生移动
							{
								game[low + 1][column] = game[low_new][column];
								game[low_new][column] = '.';
							}
						}
						break;//结束循环
					}
			}
}
void move_down(unsigned int game[][N], long double * p, long double * s)
{
	int low, column, low_new;//low与column为原始数据的行列，low_new为新数据行

	for (column = 0; column < N; column++)
		for (low = N - 1; low > 0; low--)
			if ('.' == game[low][column])//原始数据未变化
			{
				for (low_new = low - 1; low_new >= 0; low_new--)
				{
					if (game[low_new][column] != '.')//新数据已经变化
					{
						//将新数据代替原始数据
						game[low][column] = game[low_new][column];
						game[low_new][column] = '.';
						break;//结束循环
					}
				}
			}
			else	//原始数据已经变化不为'.'
			{
				for (low_new = low - 1; low_new >= 0; low_new--)
					if (game[low_new][column] != '.')//新数据已经变化
					{
						if (game[low][column] == game[low_new][column])//数据可累加情况
						{
							game[low][column] += game[low][column];
							game[low_new][column] = '.';
							*p = (double)game[low][column];
							*s = *s + *p;
						}
						else//数据不可累加情况
						{
							if (low - low_new != 1)//新数据与原数据间隔不为1时发生移动
							{
								game[low - 1][column] = game[low_new][column];
								game[low_new][column] = '.';
							}
						}
						break;//结束循环
					}
			}
}
void move_left(unsigned int game[][N], long double * p, long double * s)
{
	int column, low, column_new;//low与column为原始数据的行列，column_new为新数据行

	for (low = 0; low < N; low++)
		for (column = 0; column < N - 1; column++)
			if ('.' == game[low][column])//原始数据未变化
			{
				for (column_new = column + 1; column_new < N; column_new++)
				{
					if (game[low][column_new] != '.')//新数据已经变化
					{
						//将新数据代替原始数据
						game[low][column] = game[low][column_new];
						game[low][column_new] = '.';
						break;//结束循环
					}
				}
			}
			else	//原始数据已经变化不为'.'
			{
				for (column_new = column + 1; column_new < N; column_new++)
					if (game[low][column_new] != '.')//新数据已经变化
					{
						if (game[low][column] == game[low][column_new])//数据可累加情况
						{
							game[low][column] += game[low][column];
							game[low][column_new] = '.';
							*p = (double)game[low][column];
							*s = *s + *p;
						}
						else//数据不可累加情况
						{
							if (column_new - column != 1)//新数据与原数据间隔不为1时发生移动
							{
								game[low][column + 1] = game[low][column_new];
								game[low][column_new] = '.';
							}
						}
						break;//结束循环
					}
			}
}
void move_right(unsigned int game[][N], long double * p, long double * s)
{
	int column, low, column_new;//low与column为原始数据的行列，column_new为新数据行

	for (low = 0; low < N; low++)
		for (column = N - 1; column > 0; column--)
			if ('.' == game[low][column])//原始数据未变化
			{
				for (column_new = column - 1; column_new >= 0; column_new--)
				{
					if (game[low][column_new] != '.')//新数据已经变化
					{
						//将新数据代替原始数据
						game[low][column] = game[low][column_new];
						game[low][column_new] = '.';
						break;//结束循环
					}
				}
			}
			else	//原始数据已经变化不为'.'
			{
				for (column_new = column - 1; column_new >= 0; column_new--)
					if (game[low][column_new] != '.')//新数据已经变化
					{
						if (game[low][column] == game[low][column_new])//数据可累加情况
						{
							game[low][column] += game[low][column];
							game[low][column_new] = '.';
							*p = (double)game[low][column];
							*s = *s + *p;
						}
						else//数据不可累加情况
						{
							if (column - column_new != 1)//新数据与原数据间隔不为1时发生移动
							{
								game[low][column - 1] = game[low][column_new];
								game[low][column_new] = '.';
							}
						}
						break;//结束循环
					}
			}
}
