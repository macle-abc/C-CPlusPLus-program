#include "mainUIData.h"

MainUI mainUI = { TRUE, TRUE, TRUE, TRUE, TRUE, FALSE};
extern double winwidth;
extern double winheight;

extern DataSystem dataSystem;

extern SortUI sortUI;
extern SearchUI searchUI;
extern CourseUI courseUI;
extern StudentUI studentUI;
extern FileUI fileUI;


static void allUIClose()
{
	AllMainUIClose();
	AllSortUIClose();
	AllSearchUIClose();
	AllCourseUIClose();
	allStuUIClose();
	allFileUIClose();
}

//enum SystemUI
//{
//	mainS,
//	fileS,
//	studentS,
//	courseS,
//	searchS,
//	sortS,
//	helpS
//};
//
//static void UICloseExceWhich(enum SystemUI syUI)
//{
//	allCouUIClose();
//	switch (syUI)
//	{
//	case mainS:
//		mainUI.m_LabelVisible = 1;
//		mainUI.m_MenuVisible = 1;
//		mainUI.m_StatusVisible = 1;
//		mainUI.m_ToolVisible = 1;
//		mainUI.m_WinVisible = 1;
//		break;
//	case fileS:
//		break;
//	case studentS:
//		break;
//	case courseS:
//		break;
//	case searchS:
//		break;
//	case sortS:
//		break;
//	default:
//		break;
//	}
//}
////
////
//static void setVisible()
//{
//
//}
static void recMain()
{
	allUIClose();
	SetMainUIMemberVisible(menuMain);
	SetMainUIMemberVisible(toolMain);
	SetMainUIMemberVisible(statusMain);
}
void AllMainUIClose()
{
	mainUI.m_LabelVisible = 0;
	mainUI.m_MenuVisible = 0;
	mainUI.m_ToolVisible = 0;
	mainUI.m_StatusVisible = 0;
}
void SetMainUIMemberVisible(whichMain which)
{
	switch (which)
	{
	case labelMain:
		mainUI.m_LabelVisible = 1;
		break;
	case menuMain:
		mainUI.m_MenuVisible = 1;
		break;
	case toolMain:
		mainUI.m_ToolVisible = 1;
		break;
	case statusMain:
		mainUI.m_StatusVisible = 1;
		break;
	default:
		break;
	}
}
void InitMainUI()
{
	mystring_init(&mainUI.m_openFilePath);
	mystring_init(&mainUI.m_saveFilePath);
	fileUI.m_textVisible = 0;
}
void MainLabelDisplay()
{
	drawLabel(winwidth / 2, winheight / 2, "欢迎使用学生信息系统");
}

void MainMenuDisplay()
{
	static char* menuFile[] = { "文件",
		"打开  | Ctrl-O",
		"保存  | Ctrl-S",
		"退出  | Ctrl-E" };
	static char* menuStudent[] = { "学生",
		"新增  | Ctrl-A",
		"删除  | Ctrl-D",
		"修改",
		"设置选修课程"
	};
	static char* menuCourse[] = { "课程",
		"新增",
		"删除",
		"修改",
		"修改分数"
	};
	static char* menuSearch[] = { "查询",
		"学生",
		"课程",
		"分数",
		"总汇"
	};
	static char* menuSort[] = { "排序",
		"分数",
		"学号",
		"姓名",
		"另存为"
	};
	static char* menuListHelp[] = { "帮助",
		"使用方法",
		"关于"
	};
	static char* selectedLabel = NULL;

	double fH = GetFontHeight();//字体高度
	double x = 0; //fH/8;
	double y = winheight;
	double h = fH * 1.5; // 控件高度
	double w = TextStringWidth(menuListHelp[0]) * 2; // 控件宽度
	double wlist = TextStringWidth(menuStudent[4]) * 1.2;
	double xindent = winheight / 20; // 缩进
	int    selection;
	char buff[128] = { 0 };
	// menu bar
	drawMenuBar(0, y - h, winwidth, h);
	// File 菜单
	selection = menuList(GenUIID(0), x, y - h, w, wlist, h, menuFile, sizeof(menuFile) / sizeof(menuFile[0]));
	if (selection == 1) //打开
	{
		strcpy(buff,GetOpenFilePath());
		mainUI.m_openFilePath.assign(&mainUI.m_openFilePath, buff);
		ReadFileToEditor(mainUI.m_openFilePath.c_str(&mainUI.m_openFilePath), &fileUI.m_textData, &fileUI.m_edit);
		recMain();
		setFileUIVisible(textFil);
	}
	if (selection == 2) //保存
	{
	
		//调用saveFile
		strcpy(buff, GetSaveFilePath());
		mainUI.m_saveFilePath.assign(&mainUI.m_saveFilePath, buff);
		WriteFileFromFileUI(mainUI.m_saveFilePath.c_str(&mainUI.m_saveFilePath));
		recMain();
		SetMainUIMemberVisible(labelMain);
	}
	if (selection == 3) //退出
		exit(-1); // choose to exit


	selection = menuList(GenUIID(0), x + w, y - h, w, wlist, h, menuStudent, sizeof(menuStudent) / sizeof(menuStudent[0]));
	if (selection == 1)
	{
		recMain();
		setStuUIVisible(addStu);
	}
	if (selection == 2)
	{
		recMain();
		setStuUIVisible(rmStu);
	}
	if (selection == 3)
	{
		recMain();
		setStuUIVisible(mvStu);
	}
	if (selection == 4)
	{
		recMain();
		setStuUIVisible(setStu);
	}

	selection = menuList(GenUIID(0), x + w * 2, y - h, w, wlist, h, menuCourse, sizeof(menuCourse) / sizeof(menuCourse[0]));
	if (selection == 1)
	{
		recMain();
		SetCourseUIMemberVisible(addRecordCourse);
	}
	if (selection == 2)
	{
		recMain();
		SetCourseUIMemberVisible(removeRecordCourse);
	}
	if (selection == 3)
	{
		recMain();
		SetCourseUIMemberVisible(modifyRecordCourse);
	}
	if (selection == 4)
	{
		recMain();
		SetCourseUIMemberVisible(setScoreCourse);
	}

	selection = menuList(GenUIID(0), x + w * 3, y - h, w, wlist, h, menuSearch, sizeof(menuSearch) / sizeof(menuSearch[0]));
	if (selection == 1)
	{
		recMain();
		SetSearchMemberUIVisible(studentSearch);
	}
	if (selection == 2)
	{
		recMain();
		SetSearchMemberUIVisible(courseSearch);
	}
	if (selection == 3)
	{
		recMain();
		SetSearchMemberUIVisible(scoreSearch);
	}
	if (selection == 4)
	{
		recMain();
		SetSearchMemberUIVisible(collectSearch);
	}

	selection = menuList(GenUIID(0), x + w * 4, y - h, w, wlist, h, menuSort, sizeof(menuSort) / sizeof(menuSort[0]));
	if (selection == 1)
	{
		recMain();
		SetSortMemberUIVisible(scoreSort);
	}
	if (selection == 2)
	{
		recMain();
		SetSortMemberUIVisible(studentIdSort);
	}
	if (selection == 3)
	{
		recMain();
		SetSortMemberUIVisible(studentNameSort);
	}
	if (selection == 4)
	{
		recMain();
		SortSaveUIDisplay();
	}
	// Help 菜单
	selection = menuList(GenUIID(0), x + w * 5, y - h, w, wlist, h, menuListHelp, sizeof(menuListHelp) / sizeof(menuListHelp[0]));
	if (selection == 2)
		ShowAbout();
	if (selection == 1)
		ShowApproach();


}

void MainToolBarDisplay()
{
	double h = GetFontHeight() * 1.5;
	double y = winheight;
	double x = 0;
	double w = TextStringWidth(" 总览学生课程信息 ");
	int k = 0;
	char* buttonName[4] = { "打开文件", "保存文件", "总览学生课程信息", "分数排序" };
	double menuAppend = TextStringWidth("设置选修课程") * 1.2;
	char buff[1024] = { 0 };
	SetPenColor("Red");
	drawLabel(0.5, y - 2 * h - menuAppend + 0.2, "工具栏");
	if (button(GenUIID(k), x, y - 2 * h - menuAppend - 0.1, w, h, buttonName[0]))
	{
		strcpy(buff, GetOpenFilePath());
		mainUI.m_openFilePath.assign(&mainUI.m_openFilePath, buff);
		ReadFileToEditor(mainUI.m_openFilePath.c_str(&mainUI.m_openFilePath), &fileUI.m_textData, &fileUI.m_edit);
		allUIClose();
		SetMainUIMemberVisible(toolMain);
		SetMainUIMemberVisible(statusMain);
		SetMainUIMemberVisible(menuMain);
		setFileUIVisible(textFil);
	}
	k++;
	if (button(GenUIID(k), x, y - 3 * h - menuAppend - 0.1, w, h, buttonName[1]))
	{
		strcpy(buff, GetSaveFilePath());
		mainUI.m_saveFilePath.assign(&mainUI.m_saveFilePath, buff);
		WriteFileFromFileUI(mainUI.m_saveFilePath.c_str(&mainUI.m_saveFilePath));
		allUIClose();
		SetMainUIMemberVisible(toolMain);
		SetMainUIMemberVisible(statusMain);
		SetMainUIMemberVisible(menuMain);
		SetMainUIMemberVisible(labelMain);
	}
	k++;
	if (button(GenUIID(k), x, y - 4 * h - menuAppend - 0.1, w, h, buttonName[2]))
	{
		recMain();
		SearchCollectUIDisplay();
		mainUI.m_LabelVisible = 0;
	}

	k++;
	if (button(GenUIID(k), x, y - 5 * h - menuAppend - 0.1, w, h, buttonName[3]))
	{
		recMain();
		SetSortMemberUIVisible(scoreSort);

	}
}

void MainStatusBarDisplay()
{
	SYSTEMTIME time;
	char date[128] = { 0 };
	char label[128] = "状态栏|        时间:";
	char fileLine[128] = { 0 };
	MovePen(0, 0.5);
	DrawLine(winwidth, 0);
	GetLocalTime(&time);
	sprintf(date, "%d-%02d-%02d %02d:%02d:%02d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	strcat(label, date);
	sprintf(fileLine, "           学生记录数:%u条    课程记录数:%u条     选修记录数:%u条", GetStudentRecords(), GetCourseRecords(), GetOptCourseRecords());
	strcat(label, fileLine);
	drawLabel(0, 0.2, label);
}

void MainUIDisplay()
{
	if (mainUI.m_MenuVisible)
		MainMenuDisplay();
	if (mainUI.m_ToolVisible)
		MainToolBarDisplay();
	if (mainUI.m_LabelVisible)
		MainLabelDisplay();
	if (mainUI.m_StatusVisible)
		MainStatusBarDisplay();
}

void InitAllUI()
{
	InitDataSystem(&dataSystem);
	ReadFileToDataSystem();
	InitMainUI();
	initFilUI();
	initStuUI();
	InitCourseUI();
	InitSearchUI();
	InitSortUI();
}
