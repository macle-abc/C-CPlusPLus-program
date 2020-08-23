#include "process.h"

//static void FullScreen() 
//{
//	HWND hwnd = GetForegroundWindow();
//	int x = GetSystemMetrics(SM_CXSCREEN) + 300;
//	int y = GetSystemMetrics(SM_CYSCREEN) + 300;
//	char setting[30];
//	sprintf(setting, "mode con:cols=%d lines=%d", x, y);
//	system(setting);
//	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, x + 300, y + 300, NULL);
//	MoveWindow(hwnd, -10, -40, x + 300, y + 300, 1);
//	printf("\n\n");
//}

Schedule& Init()
{
	//FullScreen();
	hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	bitMap = CreateBitMap(65536);
	BitMapSet(bitMap, 0);
	string cpuNums = "";
	string resourceNums = "";
	cout << "请输入系统逻辑处理器数量(1-64):" << endl;
	getline(cin, cpuNums);
	regex check(R"([1-9]|([1-5][0-9])|6[0-4])");
	while (!regex_match(cpuNums, check))
	{
		cerr << "逻辑处理器数量不正确!请重新输入!" << endl;
		getline(cin, cpuNums);
	}
	cout << "请输入系统资源数量(1-100):" << endl;
	getline(cin, resourceNums);
	check = "[1-9]|[1-9][0-9]|100";
	while (!regex_match(resourceNums, check))
	{
		cerr << "系统资源数不正确!请重新输入!" << endl;
		getline(cin, resourceNums);
	}
	srand(unsigned(time(nullptr)));
	static Schedule schedule(std::stoi(cpuNums), std::stoi(resourceNums));
	cout << "即将进入进程管理系统..." << endl;
	Sleep(2000);
	system("cls");
	return schedule;
}

void Run(Schedule& schedule)
{
	regex quitXP(R"([qQ])");
	string quit;
	clock_t systemTime = 0;
	clock_t start = 0;
	clock_t end = 0;
	while (!regex_match(quit, quitXP))
	{
		ShowInterface(schedule);
		choose which = ProcessInteraction(schedule);
		if (which == choose::add)
			SystemProcess(schedule, which, systemTime);
		else if (which == choose::quit)
		{
			schedule.clear();
			BitMapDestroy(&bitMap);
			exit(0);
		}
		else
			SystemProcess(schedule, which);
		start = clock();
		end = clock();
		while (((double)(end - start) / CLOCKS_PER_SEC) < 1) //阻塞1秒以模拟真实环境
		{
			end = clock();
		}
		systemTime++;
		system("cls");
	}
}

choose ProcessInteraction(Schedule& schedule)
{
	choose which = choose::other;
	if (_kbhit())
	{
		ShowOptionArea();
		string chooseTemp;
		getline(cin, chooseTemp);
		regex chooseXP(R"([1-3])");
		while (!regex_match(chooseTemp, chooseXP))
		{
			//printXY(16, 0, "格式有错误!请重新输入!");
			Location(16, 0);
			cerr << "格式有误!请重新输入!" << endl;
			Location(16, 1);
			getline(cin, chooseTemp);
		}
		int result =  std::stoi(chooseTemp);
		switch (result)
		{
		case 1:
			which = choose::add;
			break;
		case 2:
			which = choose::kill;
			break;
		case 3:
			which = choose::quit;
			break;
		default:
			break;
		}
	}
	return which;
}

void SystemProcess(Schedule& schedule, choose which, ...)
{
	va_list args;
	va_start(args, which);
	if (which == choose::add)
	{

		ShowOptionArea();
		string pName;
		Location(16, 0);
		cout << "请输入进程名:";
		//printXY(16, 0, "请输入进程名:");
		getline(cin, pName);
		string owner;
		Location(16, 1);
		cout << "请输入进程拥有者:";
		//printXY(16, 1, "请输入进程拥有者:");
		getline(cin, owner);
		clock_t estimatedTime = 0;
		string temp;
		Location(16, 2);
		cout << "请输入进程预计完成时间:";
		//printXY(16, 2, "请输入进程预计完成时间:");
		getline(cin, temp);
		regex timeXP(R"(\d+)");
		while (!regex_match(temp, timeXP))
		{
			Location(16, 3);
			cerr << "预计完成时间输入有误!请重新输入!" << endl;
			Location(16, 4);
			getline(cin, temp);
			//printXY(16, 3, "预计完成时间输入有误!请重新输入!");
		}
		estimatedTime = std::stol(temp);
		clock_t systemTime = va_arg(args, clock_t);
		PCB pcb(pName, PCB::ready, owner, estimatedTime, systemTime);
		schedule.AddProcessToReadyQueue(move(pcb));
	}
	else if (which == choose::kill)
	{

		ShowOptionArea();
		Location(16, 0);
		cout << "请输入要杀死的进程id(1-65535):";
		//printXY(16, 0, "请输入要杀死的进程id(1-65535):");
		string pidTemp;
		regex pidXP("[0-9]{1,5}");
		getline(cin, pidTemp);
		while (!regex_match(pidTemp, pidXP))
		{
		PID:
			Location(16, 1);
			cerr << "id格式有误!请重新输入!" << endl;
			//printXY(16, 1, "id格式有误!请重新输入!");
			Location(16, 2);
			getline(cin, pidTemp);
		}
		uint16_t pid = std::stoul(pidTemp);
		if (pid == 0)
			goto PID;
		schedule.KillRunning(pid);
	}
	schedule.ReadyToRunning();
	schedule.Running(70);
	schedule.RunningToEnd();
	schedule.WaitToReady();
	va_end(args);
}
