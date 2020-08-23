#include "SearchUI.h"

extern DataSystem searchResult;
extern DataSystem dataSystem;
SearchUI searchUI;

void InitSearchUI()
{
	AllSearchUIClose();
	InitDataSystem(&searchResult);
	mystring_init(&searchUI.m_textData);
	mystring_init(&searchUI.m_editor.m_srcData);
}

void AllSearchUIClose()
{
	searchUI.m_courseUIVisible = 0;
	searchUI.m_collectUIVisible = 0;
	searchUI.m_scoreUIVisible = 0;
	searchUI.m_studentUIVisible = 0;
	searchUI.m_editorUIVisible = 0;
}

void SetSearchMemberUIVisible(whichSea which)
{
	switch (which)
	{
	case courseSearch:
		searchUI.m_courseUIVisible = 1;
		break;
	case collectSearch:
		searchUI.m_collectUIVisible = 1;
		break;
	case scoreSearch:
		searchUI.m_scoreUIVisible = 1;
		break;
	case studentSearch:
		searchUI.m_studentUIVisible = 1;
		break;
	case editorSearch:
		searchUI.m_editorUIVisible = 1;
		break;
	default:
		break;
	}
}

void SearchUIDisplay()
{
	if (searchUI.m_courseUIVisible)
		SearchCourseUIDisplay();
	if (searchUI.m_collectUIVisible)
		SearchCollectUIDisplay();
	if (searchUI.m_scoreUIVisible)
		SearchScoreUIDisplay();
	if (searchUI.m_studentUIVisible)
		SearchStudentUIDisplay();
	if (searchUI.m_editorUIVisible)
		SearchEditorUIDisplay();
}

void SearchStudentUIDisplay()
{
	double x = TextStringWidth("总览课程信息") + 1;
	double y = 6.5;
	double w = 7.0;
	double h = GetFontHeight() + 0.2;
	static char buff[][1024] = { "", "", "", "" };
	//	char label[][1024] = { "学号(8位数字):", "姓名:", "班级(9位数字):", "专业:", "性别(男:M 女:W):" };
	char major[1024] = { 0 };
	char name[1024] = { 0 };
	unsigned id = 0;
	unsigned class = 0;
	if (button(GenUIID(0), x + w / 2, y -= h * 1.2 + h * 0.7, w / 4, h, "通过班级号查询"))
	{
		ReadFileToDataSystem();
		CHECK_AND_PROMPT("班级号非法!应为9位数字!", buff[0], 9);
		/*if (!check(buff[0], 9))
		{
			MessageBox(NULL, "班级号非法!应为9位数字!", "输入错误!", MB_ICONHAND);
			return;
		}*/
		sscanf(buff[0], "%u", &class);
		//显示结果
		FindAndSave(SearchStudentByClass, student, &class);
		WriteFileFromStuList("../DataSystem/Data/stuResult.txt", &searchResult.m_studentTable, "w");
		ReadFileToEditor("../DataSystem/Data/stuResult.txt", &searchUI.m_textData, &searchUI.m_editor);
		searchUI.m_editorUIVisible = 1;
		searchUI.m_studentUIVisible = 0;
	}
	SetPenColor("Brown");
	drawLabel(x - h / 2 - TextStringWidth("姓"), (y -= h * 1.2) + h * 0.7 - 0.2, "请输入班级号");
	if (textbox(GenUIID(0), x + 0.8, y, w, h, buff[0], 1024))
		;
	if (button(GenUIID(0), x + w / 2, y -= h * 1.2 + h * 0.7, w / 4, h, "通过学生姓名查询"))
	{
		ReadFileToDataSystem();
		CHECK_AND_PROMPT("姓名过长!不应超过10个字符", buff[1], 10);
		/*if (!check(buff[1], 10))
		{
			MessageBox(NULL, "姓名过长!不应超过10个字符", "输入错误!", MB_ICONHAND);
			return;
		}*/
		sscanf(buff[1], "%s", name);
		//显示结果
		FindAndSave(SearchStudentByName, student, name);
		WriteFileFromStuList("../DataSystem/Data/stuResult.txt", &searchResult.m_studentTable, "w");
		ReadFileToEditor("../DataSystem/Data/stuResult.txt", &searchUI.m_textData, &searchUI.m_editor);
		searchUI.m_editorUIVisible = 1;
		searchUI.m_studentUIVisible = 0;
	}
	SetPenColor("Brown");
	drawLabel(x - h / 2 - TextStringWidth("姓"), (y -= h * 1.2) + h * 0.7 - 0.2, "请输入学生姓名");
	if (textbox(GenUIID(0), x + 0.8, y, w, h, buff[1], 1024))
		;
	if (button(GenUIID(0), x + w / 2, y -= h * 1.2 + h * 0.7, w / 4, h, "通过学生学号查询"))
	{
		ReadFileToDataSystem();
		CHECK_AND_PROMPT("学号非法!应为8位数字", buff[2], 8);
	/*	if (!check(buff[2], 8))
		{
			MessageBox(NULL, "学号非法!应为8位数字!", "输入错误!", MB_ICONHAND);
			return;
		}*/
		sscanf(buff[2], "%u", &id);
		//显示结果
		FindAndSave(SearchStudentById, student, &id);
		WriteFileFromStuList("../DataSystem/Data/stuResult.txt", &searchResult.m_studentTable, "w");
		ReadFileToEditor("../DataSystem/Data/stuResult.txt", &searchUI.m_textData, &searchUI.m_editor);
		searchUI.m_editorUIVisible = 1;
		searchUI.m_studentUIVisible = 0;
	}
	SetPenColor("Brown");
	drawLabel(x - h / 2 - TextStringWidth("姓"), (y -= h * 1.2) + h * 0.7 - 0.2, "请输入学生学号");
	if (textbox(GenUIID(0), x + 0.8, y, w, h, buff[2], 1024))
		;
	if (button(GenUIID(0), x + w / 2, y -= h * 1.2 + h * 0.7, w / 4, h, "通过专业查询"))
	{
		ReadFileToDataSystem();
		CHECK_AND_PROMPT("专业过长!不应超过10个字符", buff[3], 10);
	/*	if (!check(buff[3], 10))
		{
			MessageBox(NULL, "专业过长!不应超过10个字符", "输入错误!", MB_ICONHAND);
			return;
		}*/
		sscanf(buff[3], "%s", major);
		//显示结果
		FindAndSave(SearchStudentByMajor,  student, major);
		WriteFileFromStuList("../DataSystem/Data/stuResult.txt", &searchResult.m_studentTable, "w");
		ReadFileToEditor("../DataSystem/Data/stuResult.txt", &searchUI.m_textData, &searchUI.m_editor);
		searchUI.m_editorUIVisible = 1;
		searchUI.m_studentUIVisible = 0;
	}
	SetPenColor("Brown");
	drawLabel(x - h / 2 - TextStringWidth("姓"), (y -= h * 1.2) + h * 0.7 - 0.2, "请输入专业");
	if (textbox(GenUIID(0), x + 0.8, y, w, h, buff[3], 1024))
		;
}

void SearchCourseUIDisplay()
{
	double x = TextStringWidth("总览课程信息") + 1;
	double y = 6.5;
	double w = 7.0;
	double h = GetFontHeight() + 0.2;
	static char buff[][1024] = { "", "", ""};
	char cId[1024] = { 0 };
	char cName[1024] = { 0 };
	char cTea[1024] = { 0 };
	if (button(GenUIID(0), x + w / 2, y -= h * 1.2 + h * 0.7, w / 4, h, "通过课程名查询"))
	{
		ReadFileToDataSystem();
		CHECK_AND_PROMPT("课程名过长!不应超过10个字符", buff[0], 10);
		//if (!check(buff[0], 10))
		//{
		//	MessageBox(NULL, "课程名过长!不应超过10个字符", "输入错误!", MB_ICONHAND);
		//	return;
		//}
		sscanf(buff[0], "%s", cName);
		//显示结果
		FindAndSave(SearchCourseByName, course, cName);
		WriteFileFromCouList("../DataSystem/Data/couResult.txt", &searchResult.m_courseTable, "w");
		ReadFileToEditor("../DataSystem/Data/couResult.txt", &searchUI.m_textData, &searchUI.m_editor);
		searchUI.m_editorUIVisible = 1;
		searchUI.m_courseUIVisible = 0;
	}
	SetPenColor("Brown");
	drawLabel(x - h / 2 - TextStringWidth("姓"), (y -= h * 1.2) + h * 0.7 - 0.2, "请输入课程名");
	if (textbox(GenUIID(0), x + 0.8, y, w, h, buff[0], 1024))
		;
	if (button(GenUIID(0), x + w / 2, y -= h * 1.2 + h * 0.7, w / 4, h, "通过课程号查询"))
	{
		ReadFileToDataSystem();
		CHECK_AND_PROMPT("课程号过长!不应超过10个字符", buff[1], 10);
	/*	if (!check(buff[1], 10))
		{
			MessageBox(NULL, "课程号过长!不应超过10个字符", "输入错误!", MB_ICONHAND);
			return;
		}*/
		sscanf(buff[1], "%s", cId);
		//显示结果
		FindAndSave(SearchCoureById, course, cName);
		WriteFileFromCouList("../DataSystem/Data/couResult.txt", &searchResult.m_courseTable, "w");
		ReadFileToEditor("../DataSystem/Data/couResult.txt", &searchUI.m_textData, &searchUI.m_editor);
		searchUI.m_editorUIVisible = 1;
		searchUI.m_courseUIVisible = 0;
	}
	SetPenColor("Brown");
	drawLabel(x - h / 2 - TextStringWidth("姓"), (y -= h * 1.2) + h * 0.7 - 0.2, "请输入课程号");
	if (textbox(GenUIID(0), x + 0.8, y, w, h, buff[1], 1024))
		;
	if (button(GenUIID(0), x + w / 2, y -= h * 1.2 + h * 0.7, w / 4, h, "通过教师名查询"))
	{
		ReadFileToDataSystem();
		CHECK_AND_PROMPT("教师名过长!不应超过10个字符", buff[2], 10);
	/*	if (!check(buff[2], 10))
		{
			MessageBox(NULL, "教师名过长!不应超过10个字符", "输入错误!", MB_ICONHAND);
			return;
		}*/
		sscanf(buff[2], "%s", cTea);
		//显示结果
		FindAndSave(SearchCourseByTeacher, course, cName);
		WriteFileFromCouList("../DataSystem/Data/couResult.txt", &searchResult.m_courseTable, "w");
		ReadFileToEditor("../DataSystem/Data/couResult.txt", &searchUI.m_textData, &searchUI.m_editor);
		searchUI.m_editorUIVisible = 1;
		searchUI.m_courseUIVisible = 0;
	}
	SetPenColor("Brown");
	drawLabel(x - h / 2 - TextStringWidth("姓"), (y -= h * 1.2) + h * 0.7 - 0.2, "请输入教师名");
	if (textbox(GenUIID(0), x + 0.8, y, w, h, buff[2], 1024))
		;
}

void SearchScoreUIDisplay()
{
	double x = TextStringWidth("总览课程信息") + 1;
	double y = 6.5;
	double w = 7.0;
	double h = GetFontHeight() + 0.2;
	static char buff[][1024] = { "", "", "" };
	char cId[1024] = { 0 };
	unsigned sid = 0;
	double score = 0.0;
	if (button(GenUIID(0), x + w / 2, y -= h * 1.2 + h * 0.7, w / 4, h, "通过课程名查询"))
	{
		ReadFileToDataSystem();
		CHECK_AND_PROMPT("课程名过长!不应超过10个字符", buff[0], 10);
	/*	if (!check(buff[0], 10))
		{
			MessageBox(NULL, "课程名过长!不应超过10个字符", "输入错误!", MB_ICONHAND);
			return;
		}*/
		sscanf(buff[0], "%s", cId);
		//显示结果
		FindAndSave(SearchOptCourseByCourseId, optCourse, cId);
		WriteFileFromOptCourseList("../DataSystem/Data/optResult.txt", &searchResult.m_optCourseTable, "w");
		ReadFileToEditor("../DataSystem/Data/optResult.txt", &searchUI.m_textData, &searchUI.m_editor);
		searchUI.m_editorUIVisible = 1;
		searchUI.m_scoreUIVisible = 0;
	}
	SetPenColor("Brown");
	drawLabel(x - h / 2 - TextStringWidth("姓"), (y -= h * 1.2) + h * 0.7 - 0.2, "请输入课程名");
	if (textbox(GenUIID(0), x + 0.8, y, w, h, buff[0], 1024))
		;
	if (button(GenUIID(0), x + w / 2, y -= h * 1.2 + h * 0.7, w / 4, h, "通过学号查询"))
	{
		ReadFileToDataSystem();
		CHECK_AND_PROMPT("学号非法!应为8位数字", buff[1], 8);
	/*	if (!check(buff[1], 8))
		{
			MessageBox(NULL, "学号非法!应为8位数字", "输入错误!", MB_ICONHAND);
			return;
		}*/
		sscanf(buff[1], "%u", &sid);
		//显示结果
		FindAndSave(SearchOptCorseByStudentId, optCourse, &sid);
		WriteFileFromOptCourseList("../DataSystem/Data/optResult.txt", &searchResult.m_optCourseTable, "w");
		ReadFileToEditor("../DataSystem/Data/optResult.txt", &searchUI.m_textData, &searchUI.m_editor);
		searchUI.m_editorUIVisible = 1;
		searchUI.m_scoreUIVisible = 0;
	}
	SetPenColor("Brown");
	drawLabel(x - h / 2 - TextStringWidth("姓"), (y -= h * 1.2) + h * 0.7 - 0.2, "请输入学号");
	if (textbox(GenUIID(0), x + 0.8, y, w, h, buff[1], 1024))
		;
	if (button(GenUIID(0), x + w / 2, y -= h * 1.2 + h * 0.7, w / 4, h, "通过分数查询"))
	{
		ReadFileToDataSystem();
		CHECK_AND_PROMPT("分数非法!应为0.00-100.00之间", buff[2], 7);
	/*	if (!check(buff[2], 7))
		{
			MessageBox(NULL, "分数非法!应为0.00—100.00之间", "输入错误!", MB_ICONHAND);
			return;
		}*/
		sscanf(buff[2], "%lf", &score);
		//显示结果
		FindAndSave(SearchOptCourseByScore, score, &score);
		WriteFileFromOptCourseList("../DataSystem/Data/optResult.txt", &searchResult.m_optCourseTable, "w");
		ReadFileToEditor("../DataSystem/Data/optResult.txt", &searchUI.m_textData, &searchUI.m_editor);
		searchUI.m_editorUIVisible = 1;
		searchUI.m_scoreUIVisible = 0;
	}
	SetPenColor("Brown");
	drawLabel(x - h / 2 - TextStringWidth("姓"), (y -= h * 1.2) + h * 0.7 - 0.2, "请输入分数");
	if (textbox(GenUIID(0), x + 0.8, y, w, h, buff[2], 1024))
		;
}

void SearchCollectUIDisplay()
{	
	CollectData();
	PrintfDataSystemToString(&dataSystem, &searchUI.m_editor.m_srcData);
	if (searchUI.m_editor.m_srcData.size(&searchUI.m_editor.m_srcData) == 0)
	{
		fprintf(stderr, "No data!");
		error;
		return;
	}
	SplitLine(searchUI.m_editor.m_srcData.c_str(&searchUI.m_editor.m_srcData), &searchUI.m_editor.m_formateData, &searchUI.m_editor.m_lines);
	searchUI.m_collectUIVisible = 0;
	searchUI.m_editorUIVisible = 1;
}

void SearchEditorUIDisplay()
{
	DrawEditor(TextStringWidth("纵览课程信息") + 1, 1.0, 7.5, 5.5, &searchUI.m_editor);
}
