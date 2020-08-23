#ifndef HEAD_GAME_H_
#define HEAD_GAME_H_

#define N 4
void show(unsigned int[][N]);//用于展示游戏数据
void move_up(unsigned int[][N], long double *, long double *);//用于上移游戏数据
void move_down(unsigned int[][N], long double *, long double *);//用于下移游戏数据
void move_left(unsigned int[][N], long double *, long double *);//用于左移游戏数据
void move_right(unsigned int[][N], long double *, long double *);//用于右移游戏数据
void game_rand(unsigned int[][N]);//用于随机出现2或4,且出现2的几率为4的三倍
int check(unsigned int[][N]);//用于检查游戏是否结束

#endif
