#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stddef.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#include "imgui.h"
#include "mainUIData.h"
#define DEMO_MENU
#define DEMO_BUTTON
#define DEMO_ROTATE
#define DEMO_EDITBOX

/***************************************************************
 VisualStudio 2010 用户注意：
    将Character Set设置为 Use Multibyte Character Set
	否则中文显示不正常
***************************************************************/
// 旋转计时器
#define MY_ROTATE_TIMER  1
// 全局变量
double winwidth, winheight;   // 窗口尺寸

// 清屏函数，provided in libgraphics
void DisplayClear(void); 

// 用户的显示函数
void display(void); 

// 用户的字符事件响应函数
void CharEventProcess(char ch)
{
	uiGetChar(ch); // GUI字符输入
	display(); //刷新显示
}

// 用户的键盘事件响应函数
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key,event); // GUI获取键盘
	display(); // 刷新显示
}

// 用户的鼠标事件响应函数
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); //GUI获取鼠标
	display(); // 刷新显示
}


extern void startTimer(int id, int timeinterval);
// 用户的计时器时间响应函数
void TimerEventProcess(int timerID)
{
	display();
}
// 用户主程序入口
// 仅初始化执行一次
void Main() 
{
#ifdef ABC_DEBUG
	 extern void test();
#endif
	 // 初始化窗口和图形系统
	SetWindowTitle("学生信息管理系统");
	//SetWindowSize(10, 10); // 单位 - 英寸
	//SetWindowSize(15, 10);
	//SetWindowSize(10, 20);  // 如果屏幕尺寸不够，则按比例缩小
    InitGraphics();
	InitAllUI();
	// 获得窗口尺寸
	winwidth = GetWindowWidth();
	winheight = GetWindowHeight();

	registerCharEvent(CharEventProcess); // 字符
	registerKeyboardEvent(KeyboardEventProcess);// 键盘
	registerMouseEvent(MouseEventProcess);      // 鼠标
	registerTimerEvent(TimerEventProcess);      // 定时器
	startTimer(MY_ROTATE_TIMER, 50);
	// 打开控制台，方便输出变量信息，便于调试
#ifdef ABC_DEBUG
	InitConsole(); 
	test();
#endif
}

extern MainUI mainUI;
extern SortUI sortUI;
extern SearchUI searchUI;
extern CourseUI courseUI;
extern StudentUI studentUI;
extern FileUI fileUI;

void display()
{
	// 清屏
	DisplayClear();	
	MainUIDisplay();
	fileUIDisplay();
	studentUIDisplay();
	CourseUIDisplay();
	SearchUIDisplay();
	SortUIDisplay();
}


