#include "control.h"
#include "view.h"

int main(int argc, const char* argv[])
{
	// 从命令行参数中获取候选人姓名
	CandidateKey* array = CheckValidityCandidates(argc, argv);
	if (!array)
		return -1;
	// 打印作者信息
	PrintDesigner("xxx", "xxx");
	// 获取投票人数
	int voters = GetVotersCount();
	size_t* candidateVotes = (size_t*)malloc(sizeof(size_t) * (argc - 1));
	if (!candidateVotes)
	{
		PrintError("Malloc Error!", true);
	}
	memset(candidateVotes, 0, sizeof(size_t) * (argc - 1));
	// 投票阶段
	for (int i = 0; i != voters; ++i)
	{
		printf("Vote:");
		char name[80] = { 0 };
		fgets(name, 80, stdin);
		name[strlen(name) - 1] = 0;
		Vote(array, candidateVotes, name, argc - 1);
	}
	// 获取获胜者信息并打印结果
	WinnerInfo winnerinfo = GetWinnerInfo(array, candidateVotes, argc - 1);
	PrintWinner(winnerinfo);
	free(array);
	free(candidateVotes);
	candidateVotes = NULL;
	array = NULL;
	return 0;
}