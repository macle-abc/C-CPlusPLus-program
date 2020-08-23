#ifndef GAME_H_
#define GAME_H_

#include "HeroWorld.h"
#include <stdio.h>
#include <string.h>

/**开始游戏
 *

 * 用于开始游戏

 * @param [in] 
    heroWorld       游戏结构地址
    isLoad          用于判断开始之前是否选择读档

 * @param [out] 
    空

 * @return 
    空

 * @note  

*/
void StartGame(HeroWorld* heroWorld, int isLoad);

#endif
