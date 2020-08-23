#include "game.h"

const char* enemyNameArr[] = { "Hydra", "Donald Trump", "Thanos", "Megatron", "Whiplash" };
void StartGame(HeroWorld* heroWorld, int isLoad)
{
	if (isLoad)
	{
		HeroWorldGameLoop(heroWorld);
	}
	else
	{
		char userName[81] = { 0 };
		printf("\nMy hero, who are you?\n");
		fgets(userName, 80, stdin);
		userName[strlen(userName) - 1] = 0;
		unsigned len = strlen(userName);
		while (len > 14 || len == 0)
		{
			printf("Illegal name! Only 1-14 characters.\n");
			printf("My hero, who are you?\n");
			fgets(userName, 80, stdin);
			len = strlen(userName);
		}

		InitHeroWorld(heroWorld, userName, enemyNameArr[(int)(5 * MYRAND)]);
		HeroWorldGameLoop(heroWorld);
	}
}
