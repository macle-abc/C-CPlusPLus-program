#ifndef CONTROL
#define CONTROL
#include "model.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/// <summary>
/// 打印错误信息并决定是否退出程序
/// </summary>
/// <param name="error">错误信息</param>
/// <param name="isExit">是否退出程序</param>
void PrintError(const char* error, bool isExit);

/// <summary>
/// 检查候选人有效性
/// </summary>
/// <param name="argc">main中argc</param>
/// <param name="argv">main中argv</param>
/// <returns>如果有效则返回候选人数目及其姓名，否则返回NULL</returns>
CandidateKey* CheckValidityCandidates(int argc, const char* argv[]);

/// <summary>
/// 检查投票人数有效性
/// </summary>
/// <param name="number">输入的投票人数</param>
/// <returns>是否有效</returns>
bool CheckValidityVoters(int number);

/// <summary>
/// 获取投票人数
/// </summary>
/// <returns>合法的投票人数</returns>
int GetVotersCount();

/// <summary>
/// 从array中寻找name的下标，然后根据该下标索引到对应的candidateVotes中，从而进行投票
/// </summary>
/// <param name="array">候选人信息</param>
/// <param name="candidateVotes">候选人得票情况</param>
/// <param name="name">投票至候选人的姓名</param>
/// <param name="count">候选人总数</param>
void Vote(CandidateKey* array, size_t* candidateVotes, const char* name, size_t count);



/// <summary>
/// 率先从candidateVotes中获取最高票数的下标，然后根据该下标获取array中的name信息，从而获取到获胜者信息
/// </summary>
/// <param name="array">候选人信息</param>
/// <param name="candidateVotes">候选人得票情况</param>
/// <param name="count">候选人总数</param>
/// <returns>获胜者信息</returns>
WinnerInfo GetWinnerInfo(CandidateKey* array, size_t* candidateVotes, size_t count);

#endif