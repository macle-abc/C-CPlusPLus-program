#ifndef MODEL
#define MODEL
#include <string.h>

/// <summary>
/// 候选人姓名
/// </summary>
typedef struct
{
	char name[80]; 
}CandidateKey;

/// <summary>
/// 获胜者信息
/// </summary>
typedef struct
{
	size_t count; // 获胜者总数
	int index[9]; // 获胜者下标
	const char* name[9]; // 获胜者姓名
}WinnerInfo;

/// <summary>
/// 获取name在array中对应的下标
/// </summary>
/// <param name="array">候选人数组</param>
/// <param name="name">需要获取下标的name</param>
/// <param name="count">候选人总数</param>
/// <returns>若name存在则返回对应的下标，否则返回-1</returns>
int GetKeyIndex(CandidateKey* array, const char* name, int count);

#endif
