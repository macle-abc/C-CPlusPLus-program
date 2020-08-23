#include "Show.h"
using std::cout;
using std::endl;
void printXY(short x, short y, const string& str)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(hstdout, coord);
	WriteConsole(hstdout, str.c_str(), str.length(), NULL, NULL);
}

void Location(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(hstdout, coord);
}
void ShowFunctionalArea()
{
	static const string function =
		"  功能区      |\n"
		"1.创建进程    |\n"
		"2.撤销进程    |\n"
		"3.退出        |\n"
		"              |\n"
		"              |\n"
		"              |\n";
	Location(0, 0);
	cout << function;
//	printXY(0, 0, function);
}

void ShowStatusBar(const Schedule& schedule)
{
	static const string statusBar = "    状态图";
	Location(71, 0);
	cout << statusBar << endl;
//	printXY(71, 0, statusBar);
	string runInfo = "";
	int num = 0;
	for (auto&& it : schedule.GetRunningProcess())
	{
		runInfo += "    运行:";
		runInfo += "pName:" + it.first.GetPName();
		runInfo += "\t  pid:";
		runInfo += std::to_string(it.first.GetPid());
		Location(71, ++num);
		cout << runInfo << endl;
//		printXY(71, ++num, runInfo);
		runInfo = "";
	}
}

void ShowOptionArea()
{
	for (int i = 0; i != 8; ++i)
	{
		Location(70, i);
		cout << "|";
	}
	COORD coord;
	coord.X = 16;
	coord.Y = 0;
	SetConsoleCursorPosition(hstdout, coord);
}
void ShowProcessStatusArea(const Schedule& schedule)
{
	static const string processStatusInfo =
		"-----------------------------------------------------------------------\n"
		"                                状态栏                                |\n"
		"   pid   |   pName   |   status   |   owner   |   eTime   |   rTime   |\n";
//	Location(0, 7);
//	cout << processStatusInfo;
	printXY(0, 7, processStatusInfo);
	//不足5个全部显示，超过5个显示最先的5
	//就绪队列
	char buff[1024] = { 0 };
	int count = 0;
	int sum = 0;
	for (auto&& it : schedule.GetReadyQueue())
	{
		if (count++ == 5)
			break;
		snprintf(buff, 72, "%9d|%11s|%12s|%11s|%11d|%11d|", it.second.first.GetPid(), it.second.first.GetPName().c_str(),
			"ready", it.second.first.GetOwner().c_str(),
			it.second.first.GetEstimatedTime(),
			it.second.first.GetRemainingTime() ? it.second.first.GetRemainingTime() : 0
		);
		Location(0, sum + 10);
		sum++;
		cout << buff << endl;
//		printXY(0, 10 + sum, buff);
	}
	count = 0;
	//等待队列
	for (auto&& it : schedule.GetWaitQueue())
	{
		if (count++ == 5)
			break;
		snprintf(buff, 72, "%9d|%11s|%12s|%11s|%11d|%11d|", it.first.GetPid(), it.first.GetPName().c_str(),
			"wait", it.first.GetOwner().c_str(),
			it.first.GetEstimatedTime(), 
			it.first.GetRemainingTime() ? it.first.GetRemainingTime() : 0
		);
		Location(0, sum + 10);
		sum++;
		cout << buff << endl;
//		printXY(0, sum + 10, buff);
	}
	count = 0;
	Location(0, sum + 10);
	cout << "-----------------------------------------------------------------------" << endl;
//	printXY(0, 10 + sum, "-----------------------------------------------------------------------");
}

void SetCursorPosition(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(hstdout, coord);
}
void ShowInterface(const Schedule& schedule)
{
	ShowFunctionalArea();
	ShowOptionArea();
	ShowProcessStatusArea(schedule);
	ShowStatusBar(schedule);
	ShowResource(schedule);
}

void ShowResource(const Schedule& schedule)
{
	Location(74, 10);
	cout << "     cpu (Unused/All) " << endl;
	Location(74, 11);
	cout << schedule.GetAvailableCPUNums() << "/" << schedule.GetCPUNums() << endl;
	Location(74, 12);
	cout << "resource (Unused/All) " << endl;
	Location(74, 13);
	cout << schedule.GetAvailableResourceNums() << "/" << schedule.GetResourceNums() << endl;
}
