#define _CRT_SECURE_NO_WARNINGS
#include "ui.h"
#include "game.h"
#include "Hero.h"
#include <conio.h>

static void GameLoop()
{
	int isload = 0;
	HeroWorld heroWorld;
	while (1)
	{
		PrintIntroduction();
		char ch = _getch();
		switch (ch)
		{
		case 'h':
		case 'H':
			PrintHelp();
			_getch();
			break;
		case '\x1b':
			PrintBye();
			exit(0);
			break;
		case ' ':
			// ¿ªÊ¼ÓÎÏ·
			StartGame(&heroWorld, isload);
			break;
		case 'l':
		case 'L':
			isload = 1;
			printf("\nLoad! Please Enter Hero Name !\n");
			char buff[81] = { 0 };
			fgets(buff, 80, stdin);
			buff[strlen(buff) - 1] = 0;
			InitHeroWorld(&heroWorld, buff, "");
			LoadHeroWorld(&heroWorld);
		default:
			break;
		}
	}
}

HANDLE hstdout;
int main(void)
{
	system("mode con cols=120 lines=30");
	hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	GameLoop();
	return 0;
}