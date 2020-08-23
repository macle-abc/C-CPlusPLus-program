#ifndef VIEW
#define VIEW
#include "model.h"
#include <stdio.h>

/// <summary>
/// 打印作者信息
/// </summary>
/// <param name="author">作者姓名</param>
/// <param name="id">作者学号</param>
void PrintDesigner(const char* author, const char* id);

/// <summary>
/// 打印获胜者信息
/// </summary>
/// <param name="winnerInfo">获胜者信息</param>
void PrintWinner(WinnerInfo winnerInfo);

#endif