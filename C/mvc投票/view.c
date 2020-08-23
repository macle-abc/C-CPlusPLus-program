#include "view.h"

void PrintDesigner(const char* author, const char* id)
{
	printf("This Program is designed and coded by %s student id %s\n", author, id);
}

void PrintWinner(WinnerInfo winnerInfo)
{
	for (size_t i = 0; i != winnerInfo.count; ++i)
	{
		printf("%s is the winner!\n", winnerInfo.name[winnerInfo.index[i]]);
	}
}
