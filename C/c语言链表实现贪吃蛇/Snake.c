#include "Snake.h"
#define _CRT_SECURE_NO_WARNINGS

void initGameMap(Map m)
{
	for (int low = 0; low < ROWMAX; ++low)
		for (int column = 0; column < COLUMNMAX; ++column)
		{
			if (0 == low || ROWMAX - 1 == low)
				m[low][column] = rowBorder;
			else if (0 == column || COLUMNMAX - 1 == column)
				m[low][column] = columnBorder;
			else
				m[low][column] = map;
		}
}

void addSnakeToMap(Map m, Snake * SnakeHeader)
{
	Snake * pCurrent = SnakeHeader->next;
	m[pCurrent->x][pCurrent->y] = snakeHead;
	pCurrent = pCurrent->next;
	while (pCurrent)
	{
		m[pCurrent->x][pCurrent->y] = snakeBody;
		pCurrent = pCurrent->next;
	}
}

void printGame(Map m)
{
	for (int low = 0; low < ROWMAX; ++low)
	{
		for (int column = 0; column < COLUMNMAX; ++column)
		{
			if (m[low][column] == rowBorder)
				printf("%c", '-');
			else if (m[low][column] == columnBorder)
				printf("%c", '|');
			else if (m[low][column] == map)
				printf("%c", ' ');
			else if (m[low][column] == snakeBody)
				printf("%c", '$');
			else if (m[low][column] == snakeHead)
				printf("%c", '@');
			else if (m[low][column] == food)
				printf("%c", '*');
		}
		printf("\n");
	}
}

void produceFood(Snake * SnakeHeader, Map m, Food * f)
{
	srand((unsigned)time(NULL));
	Snake * pCurrent = NULL;
	int x = 0;
	int y = 0;
	while (true)
	{
		x = rand() % ROWMAX;
		y = rand() % COLUMNMAX;
		pCurrent = SnakeHeader->next;
		while (pCurrent)
		{
			if (pCurrent->x == x && pCurrent->y == y)
				break;
			pCurrent = pCurrent->next;
		}
		if (pCurrent == NULL && !pointOverstep(x, y))
			break;
	}
	f->x = x;
	f->y = y;
	m[x][y] = food;
}

void gameFlow(void)
{
	//初始化
	Map map = { 0 };
	Snake * snake = initSnake();
	Food f = { 0, 0};
	UserInfo user = { 0, 0 ,0 };
	unsigned speed = 200;
	printf("**********************************\n\t欢迎来到贪吃蛇小游戏\n**********************************\n\n\n");
	printf("以小写字母a代表向左移动，小写字母d代表向右移动\n");
	printf("以小写字母w代表向上移动，小写字母s代表向下移动\n\n");
	printf("请输入您的姓名以便记录分数排行(回车确认输入)\n");
	gets(user.name);
	printf("3秒后即将进入游戏...\n");
	Sleep(3000);
	system("CLS");
	HideCursor();
	gotoxy(0, 0);
	initGameMap(map);
	addSnakeToMap(map, snake);
	produceFood(snake, map, &f);

	while (true)
	{
		printGame(map);
		printf("您的分数为:%u\n", user.score);
		if (SnakeOverStep(snake) || SnakeEatItself(snake))
		{
			freeSnake(&snake);
			UserInfo * UserHeader = NULL;
			loadUserInof(saveUserInfo(&user), &UserHeader);
			UserHeader = Sort(UserHeader);
			printf("您的排名为:第%d名\n", findByName(UserHeader, user.name));
			printf("\n");
			printfRank(UserHeader);
			freeUserInfo(&UserHeader);
			printf("\n");
			printf("游戏失败！即将退出游戏\n");
			Sleep(3000);
			exit(0);
		}
		if (user.score == (ROWMAX * COLUMNMAX - (ROWMAX + COLUMNMAX) * 2 + 4))
		{
			freeSnake(&snake);
			UserInfo * UserHeader = NULL;
			loadUserInof(saveUserInfo(&user), &UserHeader);
			UserHeader = Sort(UserHeader);
			printf("您的排名为:第%d名\n", findByName(UserHeader, user.name));
			printf("\n");
			printfRank(UserHeader);
			freeUserInfo(&UserHeader);
			printf("\n");
			printf("恭喜您成功过关！即将退出游戏\n");
			Sleep(3000);
			exit(0);
		}
		if (eatFood(snake, map,&f))
		{
			++user.score;
			initGameMap(map);
			addSnakeBody(snake);
			move(snake);
			addSnakeToMap(map, snake);
			produceFood(snake, map, &f); 
		}
		else
		{
			clearSnake(snake, map);		
			move(snake);
			addSnakeToMap(map, snake);
		}
		if (user.score % 20 == 0)
			speed /= 2;
		Sleep(speed);
		HideCursor();
		gotoxy(0, 0);
	}
}

bool eatFood(Snake * SnakeHeader, Map m, Food * f)
{
	Snake * pCurrent = SnakeHeader->next;
	for (int low = 0; low < ROWMAX; ++low)
		for (int column = 0; column < COLUMNMAX; ++column)
			if (pCurrent->x == f->x && pCurrent->y == f->y)
			{
				return true;
			}
	return false;
}

void clearSnake(Snake * SnakeHeader, Map m)
{
	Snake * pCurrent = SnakeHeader->next;
	while (pCurrent)
	{
		m[pCurrent->x][pCurrent->y] = map;
		pCurrent = pCurrent->next;
	}
}

bool SnakeEatItself(Snake * SnakeHeader)
{
	Snake * pCurrent = SnakeHeader->next;
	Snake * copy = NULL;
	while (pCurrent)
	{
		copy = pCurrent->next;
		while (copy)
		{
			if (copy->x == pCurrent->x && copy->y == pCurrent->y)
			{
				return true;
			}
			copy = copy->next;
		}
		pCurrent = pCurrent->next;
	}
	return false;
}

bool SnakeOverStep(Snake * SnakeHeader)
{
	Snake * pCurrent = SnakeHeader->next;
	while (pCurrent)
	{
		if (pointOverstep(pCurrent->x, pCurrent->y))
		{
			return true;
		}
		pCurrent = pCurrent->next;
	}
	return false;
}

bool pointOverstep(int x, int y)
{
	if (x == ROWMAX - 1 || y == COLUMNMAX - 1 || x == 0 || y == 0)
		return true;
	else
		return false;
}

void addSnakeBody(Snake * SnakeHeader)
{
	Snake * pTail = SnakeHeader->next;
	while (pTail)
	{
		pTail = pTail->next;
		if (pTail->next == NULL)
			break;
	}
	Snake * newNode = (Snake *)malloc(sizeof(Snake));
	if (pTail->direction == 'w')
	{
		newNode->x = pTail->x + 1;
		newNode->y = pTail->y;
		newNode->direction = pTail->direction;
		newNode->next = NULL;
	}
	if (pTail->direction == 's')
	{
		newNode->x = pTail->x - 1;
		newNode->y = pTail->y;
		newNode->direction = pTail->direction;
		newNode->next = NULL;
	}
	if (pTail->direction == 'a')
	{
		newNode->y = pTail->y + 1;
		newNode->x = pTail->x;
		newNode->direction = pTail->direction;
		newNode->next = NULL;
	}
	if (pTail->direction == 'd')
	{
		newNode->y = pTail->y - 1;
		newNode->x = pTail->x;
		newNode->direction = pTail->direction;
		newNode->next = NULL;
	}
	pTail->next = newNode;
}

bool moveHead(Snake * SnakeHeader)
{
	char direction = SnakeHeader->direction;
	if (kbhit())
	{
		direction = getch();
	}
	if (SnakeHeader->direction == 'w' && direction == 's')
		return false;
	if (SnakeHeader->direction == 's' && direction == 'w')
		return false;
	if (SnakeHeader->direction == 'a' && direction == 'd')
		return false;
	if (SnakeHeader->direction == 'd' && direction == 'a')
		return false;
	SnakeHeader->direction = direction;
	if (SnakeHeader->direction == 'w')
		SnakeHeader->x -= 1;
	if (SnakeHeader->direction == 's')
		SnakeHeader->x += 1;
	if (SnakeHeader->direction == 'a')
		SnakeHeader->y -= 1;
	if (SnakeHeader->direction == 'd')
		SnakeHeader->y += 1;
	return true;
}

void moveBody(Snake * SnakeBody)
{
	if (SnakeBody->direction == 'w')
		SnakeBody->x -= 1;
	if (SnakeBody->direction == 's')
		SnakeBody->x += 1;
	if (SnakeBody->direction == 'a')
		SnakeBody->y -= 1;
	if (SnakeBody->direction == 'd')
		SnakeBody->y += 1;
}

void move(Snake * SnakeHeader)
{
	Snake * pCurrent = SnakeHeader->next;
	if(!moveHead(pCurrent))//蛇头移动失败
		return;
	char lastCopy = SnakeHeader->next->direction;
	char nowCopy = 0;
	pCurrent = pCurrent->next;
	while (pCurrent)
	{
		moveBody(pCurrent);
		nowCopy = pCurrent->direction;
		pCurrent->direction = lastCopy;
		lastCopy = nowCopy;
		pCurrent = pCurrent->next;
	}
}

Snake * initSnake(void)
{
	Snake * SnakeHeader = (Snake *)malloc(sizeof(Snake));
	SnakeHeader->x = -1;
	SnakeHeader->y = -1;
	SnakeHeader->direction = 0;
	SnakeHeader->next = NULL;
	Snake * pCurrent = SnakeHeader;
	for (int number = 0; number < INITSNAKENODENUM; ++number)
	{
		Snake * pNewNode = (Snake *)malloc(sizeof(Snake));
		pNewNode->y = COLUMNMAX / 2 + number;
		pNewNode->x = ROWMAX / 2;
		pNewNode->direction = 'a';
		pNewNode->next = NULL;
		pCurrent->next = pNewNode;
		pCurrent = pNewNode;
	}
	return SnakeHeader;
}

void freeSnake(Snake ** SnakeHeader)
{
	if (NULL == *SnakeHeader)
		return;
	Snake * pCurrent = *SnakeHeader;
	Snake * temp = NULL;
	while (pCurrent)
	{
		temp = pCurrent->next;
		free(pCurrent);
		pCurrent = temp;
	}
	*SnakeHeader = NULL;
	SnakeHeader = NULL;
}

void freeUserInfo(UserInfo ** UserHeader)
{
	if (NULL == *UserHeader)
		return;
	UserInfo * pCurrent = *UserHeader;
	UserInfo * temp = NULL;
	while (pCurrent)
	{
		temp = pCurrent->next;
		free(pCurrent);
		pCurrent = temp;
	}
	*UserHeader = NULL;
	UserHeader = NULL;
}

void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

 FilePath saveUserInfo(UserInfo * user)
{
	FILE * file = fopen("Ranking list.txt", "a");
	if (NULL == file)
	{
		printf("文件打开失败!\n");
		return;
	}
	fprintf(file, "姓名:%s\n", user->name);
	fprintf(file, "分数:%d\n\n", user->score);
	fclose(file);
	return "Ranking list.txt";
}

 void loadUserInof(FilePath filePath, UserInfo ** userLinkList)
 {
	 FILE * file = fopen(filePath, "r");
	 if (NULL == file)
	 {
		 printf("文件打开失败\n");
		 return;
	 }
	 (*userLinkList) = (UserInfo *)malloc(sizeof(UserInfo));
	 UserInfo * pCurrent = (*userLinkList);
	 UserInfo * temp = (UserInfo *)malloc(sizeof(UserInfo));
	 char name[80] = { 0 };
	 char score[80] = { 0 };
	 char null[4] = { 0 };
	 fgets(name, 80, file);
	 fgets(score, 80, file);
	 fgets(null, 4, file);
	 sscanf(name, "姓名:%s", temp->name);
	 sscanf(score, "分数:%u", &temp->score);
	 temp->next = NULL;
	 while (!feof(file))
	 {
		pCurrent->next = temp;
		pCurrent = pCurrent->next;
		temp = (UserInfo *)malloc(sizeof(UserInfo));
		char name[80] = { 0 };
		char score[80] = { 0 };
		char null[4] = { 0 };
		fgets(name, 80, file);
		fgets(score, 80, file);
		fgets(null, 4, file);
		sscanf(name, "姓名:%s", temp->name);
		sscanf(score, "分数:%u", &temp->score);
		temp->next = NULL;
	 }
	 fclose(file);
 }

 UserInfo * Sort(UserInfo * Header)
 {
	 UserInfo * p, *q;
	 UserInfo temp;
	 for (p = Header->next; p != NULL; p = p->next)
	 {
		 for (q = p->next; q != NULL; q = q->next)
		 {
			 if (p->score < q->score)
			 {
				 strcpy(temp.name, q->name);
				 temp.score = q->score;
				 strcpy(q->name, p->name);
				 q->score = p->score;
				 strcpy(p->name, temp.name);
				 p->score = temp.score;
			 }
		 }
	 }
	 return Header;
 }

 rank findByName(UserInfo * Header, char name[80])
 {
	 UserInfo * pCurrent = Header->next;
	 int number = 0;
	 while (pCurrent)
	 {
		 ++number;
		 if (strcmp(name, pCurrent->name) == 0)
			 break;
		 pCurrent = pCurrent->next;
	 }
	 return number;
 }

 void printfRank(UserInfo * Header)
 {
	 printf("--------------------分数排行榜--------------------\n");
	 printf("名次\t姓名\t\t\t分数\n");
	 UserInfo * pCurrent = Header->next;
	 int RankNum = 1;
	 while (pCurrent)
	 {
		 printf("%4d\t%-24s%d\n", RankNum++, pCurrent->name, pCurrent->score);
		 pCurrent = pCurrent->next;
	 }
 }