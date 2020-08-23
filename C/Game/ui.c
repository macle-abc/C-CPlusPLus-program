#include "ui.h"

void PrintXY(short x, short y, const char* str)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(hstdout, coord);
	printf("%s", str);
}

void PrintIntroduction()
{
	system("cls");
	char gameName[] = "Welcome to the HERO WORLD";
	unsigned y = 3U;
	PrintXY(30, y++, gameName);
	printf("\n");
	char operationText[][80] =
	{
		"Enter[Space] to Start the game ",
		"Enter L/l to Load",
		"Enter H/h for Help",
		"Enter [Esc] to Exit"
	};
	y += 2;
	for (int i = 0; i != 4; ++i)
	{
		PrintXY(30, y += 2, operationText[i]);
	}
}

void PrintHelp()
{
	system("cls");
	char help[][80] =
	{
		"In this game, you are going to play a hero and participate in multiple battles.",
		"If you can stay alive, you will encounter an enemy every time you fight.",
		"At the beginning of the turn, each has 100 health",
		"Each turn, you and the enemy once each operation.",
		"Wrong operation will waste the chance of this round!!!",
		"These operations include \"attack\", \"treatment\", \"buy\", \"sell\" and so on. ",
		"In this battle, if you are the winner then you can choose",
		"whether to continue and the points will be accumulated.",
		"And if you die, then the game is over and you will see your final score."
	};
	unsigned y = 3U;
	for (int i = 0; i != 9; ++i)
	{
		PrintXY(10, y += 2, help[i]);
	}
	PrintXY(10, y += 2, "Enter any key to return");
}

void PrintBye()
{
	unsigned y = 3U;
	y = 3U;
	system("cls");	
	char byeText[][80] =
	{
		"HeroWorld",
		"Goodbye, my hero! I hope you have fun in the game!",
		"The game will close after 3 seconds!"
	};
	for (int i = 0; i != 3; ++i)
	{
		PrintXY(20, y += 2, byeText[i]);
	}
	Sleep(3000);
	exit(0);
}
