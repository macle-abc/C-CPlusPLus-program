#include "CourseUI.h"

CourseUI courseUI;
extern DataSystem dataSystem;
void InitCourseUI()
{
	AllCourseUIClose();
	mystring_init(&courseUI.m_editor.m_srcData);
	mystring_init(&courseUI.m_textData);
}
void AllCourseUIClose()
{
	courseUI.m_addRecordUIVisible = 0;
	courseUI.m_modifyRecordUIVisible = 0;
	courseUI.m_removeRecordUIVisible = 0;
	courseUI.m_setScoreUIVisible = 0;
	courseUI.m_editorUIVisible = 0;
}

void SetCourseUIMemberVisible(whichCou which)
{
	switch (which)
	{
	case addRecordCourse:
		courseUI.m_addRecordUIVisible = 1;
		break;
	case removeRecordCourse:
		courseUI.m_removeRecordUIVisible = 1;
		break;
	case modifyRecordCourse:
		courseUI.m_modifyRecordUIVisible = 1;
		break;
	case setScoreCourse:
		courseUI.m_setScoreUIVisible = 1;
		break;
	case editorCourse:
		courseUI.m_editorUIVisible = 1;
		break;
	default:
		break;
	}
}

void CourseUIDisplay()
{
	if (courseUI.m_addRecordUIVisible)
		CourseAddRecordUIDisplay();
	if (courseUI.m_removeRecordUIVisible)
		CourseRemoveRecordDisplay();
	if (courseUI.m_modifyRecordUIVisible)
		CourseModifyRecordUIDisplay();
	if (courseUI.m_setScoreUIVisible)
		CourseSetScoreUIDisplay();
	if (courseUI.m_editorUIVisible)
		CourseEditorUIDisplay();
}


void CourseAddRecordUIDisplay()
{
	double x = TextStringWidth("总览课程信息") + 1;
	double y = 6.0;
	double w = 7;
	double h = GetFontHeight() + 0.4;
	static char buff[][1024] = { "", "", ""};
	char label[][1024] = { "课程号:", "课程名:", "教师名:"};
	int i = 0;
	for (; i != 3; ++i)
	{
		SetPenColor("Brown");
		drawLabel(x - h / 2 - TextStringWidth("姓"), (y -= h * 1.2) + h * 0.7, label[i]);
		if (textbox(GenUIID(i), x + 0.8, y, w, h, buff[i], 1024))
			;
	}
	if (button(GenUIID(0), x + w / 2, y -= h * 1.2 + h * 0.7, w / 2, h, "添加"))
	{
		Course temp = { NULL };
		CHECK_AND_PROMPT("课程号过长!不应超过10个字符", buff[0], 10);
		CHECK_AND_PROMPT("课程名过长!不应超过10个字符", buff[1], 10);
		CHECK_AND_PROMPT("教师名过长!不应超过10个字符", buff[2], 10);
		temp.m_cId = malloc(20);
		if (NULL == temp.m_cId)
		{
			fprintf(stderr, "Don't have enough memory");
			error;
			return;
		}
		memset(temp.m_cId, 0, 20);
		temp.m_cName = malloc(20);
		if (NULL == temp.m_cName)
		{
			fprintf(stderr, "Don't have enough memory");
			error;
			free(temp.m_cId);
			temp.m_cId = NULL;
			return;
		}
		memset(temp.m_cName, 0, 20);
		temp.m_teacher = malloc(20);
		if (NULL == temp.m_teacher)
		{
			fprintf(stderr, "Don't have enough memory");
			error;
			free(temp.m_cId);
			temp.m_cId = NULL;
			free(temp.m_cName);
			temp.m_cName = NULL;
			return;
		}
		sscanf(buff[0], "%s", temp.m_cId);
		sscanf(buff[1], "%s", temp.m_cName);
		sscanf(buff[2], "%s", temp.m_teacher);
		ReadFileToDataSystem();
		AddCourseRecord(&temp);
		free(temp.m_cId);
		free(temp.m_cName);
		free(temp.m_teacher);
		courseUI.m_editorUIVisible = 1;
		WriteFileFromCouList("../DataSystem/Data/CourseTable.txt", &dataSystem.m_courseTable, "w");
		ReadFileToEditor("../DataSystem/Data/CourseTable.txt", &courseUI.m_textData, &courseUI.m_editor);
		courseUI.m_addRecordUIVisible = 0;
	}
}

void CourseRemoveRecordDisplay()
{
	double x = TextStringWidth("总览课程信息") + 1;
	double y = 7.0;
	double w = 7.0 ;
	double h = GetFontHeight() + 0.4;
	static char buff[][1024] = { "", "", "" };
	//	char label[][1024] = { "学号(8位数字):", "姓名:", "班级(9位数字):", "专业:", "性别(男:M 女:W):" };
	unsigned tempId = 0;
	if (button(GenUIID(0), x + w / 2, y -= h * 1.2 + h * 0.7, w / 4, h, "通过课程名删除"))
	{
		CHECK_AND_PROMPT("课程名过长!不应超过10个字符", buff[0], 10);
		ReadFileToDataSystem();
		RemoveCourseRecord(RemoveCourseByName, buff[0]);
		//显示结果
		WriteFileFromCouList("../DataSystem/Data/CourseTable.txt", &dataSystem.m_courseTable, "w");
		ReadFileToEditor("../DataSystem/Data/CourseTable.txt", &courseUI.m_textData, &courseUI.m_editor);
		SetCourseUIMemberVisible(editorCourse);
		courseUI.m_removeRecordUIVisible = 0;
	}
	SetPenColor("Brown");
	drawLabel(x - h / 2 - TextStringWidth("姓"), (y -= h * 1.2) + h * 0.7 - 0.2, "请输入课程名");
	if (textbox(GenUIID(0), x + 0.8, y, w, h, buff[0], 1024))
		;
	if (button(GenUIID(0), x + w / 2, y -= h * 1.2 + h * 0.7, w / 4, h, "通过课程号删除"))
	{
		CHECK_AND_PROMPT("课程号过长!不应超过10个字符", buff[1], 10);
		ReadFileToDataSystem();
		RemoveCourseRecord(RemoveCourseByCId, buff[1]);
		//显示结果
		WriteFileFromCouList("../DataSystem/Data/CourseTable.txt", &dataSystem.m_courseTable, "w");
		ReadFileToEditor("../DataSystem/Data/CourseTable.txt", &courseUI.m_textData, &courseUI.m_editor);
		SetCourseUIMemberVisible(editorCourse);
		courseUI.m_removeRecordUIVisible = 0;
	}
	SetPenColor("Brown");
	drawLabel(x - h / 2 - TextStringWidth("姓"), (y -= h * 1.2) + h * 0.7 - 0.2, "请输入课程号");
	if (textbox(GenUIID(0), x + 0.8, y, w, h, buff[1], 1024))
		;
	if (button(GenUIID(0), x + w / 2, y -= h * 1.2 + h * 0.7, w / 4, h, "通过教师姓名删除"))
	{
		CHECK_AND_PROMPT("教师名过长!不应超过10个字符", buff[2], 10);
		ReadFileToDataSystem();
		RemoveCourseRecord(RemoveCourseByTeacher, buff[2]);
		//显示结果
		WriteFileFromCouList("../DataSystem/Data/CourseTable.txt", &dataSystem.m_courseTable, "w");
		ReadFileToEditor("../DataSystem/Data/CourseTable.txt", &courseUI.m_textData, &courseUI.m_editor);
		SetCourseUIMemberVisible(editorCourse);
		courseUI.m_removeRecordUIVisible = 0;
	}
	SetPenColor("Brown");
	drawLabel(x - h / 2 - TextStringWidth("姓"), (y -= h * 1.2) + h * 0.7 - 0.2, "请输入教师姓名");
	if (textbox(GenUIID(0), x + 0.8, y, w, h, buff[2], 1024))
		;
}

void CourseModifyRecordUIDisplay()
{
	double x = TextStringWidth("总览课程信息") + 1;
	double y = 6.0;
	double w = 7;
	double h = GetFontHeight() + 0.4;
	static char buff[][1024] = {"", "", "", ""};
	char label[][1024] = { "原始课程号:", "新课程号", "课程名", "教师名"};
	int i = 0;
	char oldCid[1024] = { 0 };
	for (; i != 4; ++i)
	{
		SetPenColor("Brown");
		drawLabel(x - h / 2 - TextStringWidth("姓"), (y -= h * 1.2) + h * 0.7, label[i]);
		if (textbox(GenUIID(i), x + 0.8, y, w, h, buff[i], 1024))
			;
	}
	if (button(GenUIID(0), x + w / 2, y -= h * 1.2 + h * 0.7, w / 2, h, "修改"))
	{
		Course temp = { NULL };
		CHECK_AND_PROMPT("课程号过长!不应超过10个字符", buff[0], 10);
		CHECK_AND_PROMPT("课程号过长!不应超过10个字符", buff[1], 10);
		CHECK_AND_PROMPT("课程名过长!不应超过10个字符", buff[2], 10);
		CHECK_AND_PROMPT("教师名过长!不应超过10个字符", buff[3], 10);
		temp.m_cId = malloc(20);
		if (NULL == temp.m_cId)
		{
			fprintf(stderr, "Don't have enough memory");
			error;
			return;
		}
		memset(temp.m_cId, 0, 20);
		temp.m_cName = malloc(20);
		if (NULL == temp.m_cName)
		{
			fprintf(stderr, "Don't have enough memory");
			error;
			free(temp.m_cId);
			temp.m_cId = NULL;
			return;
		}
		temp.m_teacher = malloc(20);
		if (NULL == temp.m_teacher)
		{
			fprintf(stderr, "Don't have enough memory");
			error;
			free(temp.m_cId);
			temp.m_cId = NULL;
			free(temp.m_cName);
			temp.m_cName = NULL;
			return;
		}
		sscanf(buff[0], "%s", oldCid);
		sscanf(buff[1], "%s", temp.m_cId);
		sscanf(buff[2], "%s", temp.m_cName);
		sscanf(buff[3], "%s", temp.m_teacher);
		ReadFileToDataSystem();
		ModifyCoruseRecord(ModifyCourseById, &oldCid, &temp);
		free(temp.m_cId);
		free(temp.m_cName);
		free(temp.m_teacher);
		courseUI.m_editorUIVisible = 1;
		WriteFileFromCouList("../DataSystem/Data/CourseTable.txt", &dataSystem.m_courseTable, "w");
		ReadFileToEditor("../DataSystem/Data/CourseTable.txt", &courseUI.m_textData, &courseUI.m_editor);
		courseUI.m_modifyRecordUIVisible = 0;
	}
}

void CourseSetScoreUIDisplay()
{
	double x = TextStringWidth("总览课程信息") + 1;
	double y = 6.0;
	double w = 7;
	double h = GetFontHeight() + 0.4;
	static char buff[][1024] = { "", "", ""};
	char label[][1024] = { "学号", "课程号", "新分数"};
	int i = 0;
	for (; i != 3; ++i)
	{
		SetPenColor("Brown");
		drawLabel(x - h / 2 - TextStringWidth("姓"), (y -= h * 1.2) + h * 0.7, label[i]);
		if (textbox(GenUIID(i), x + 0.8, y, w, h, buff[i], 1024))
			;
	}
	if (button(GenUIID(0), x + w / 2, y -= h * 1.2 + h * 0.7, w / 2, h, "修改"))
	{
		OptCourse temp = { 0 };
		CHECK_AND_PROMPT("学号非法!应为8位数字", buff[0], 8);
		CHECK_AND_PROMPT("课程名过长!不应超过10个字符", buff[1], 10);
		CHECK_AND_PROMPT("分数非法!应为0.00-100.00", buff[2], 7);
		temp.m_cId = malloc(20);
		if (NULL == temp.m_cId)
		{
			fprintf(stderr, "Don't have enough memory");
			error;
			return;
		}
		memset(temp.m_cId, 0, 20);
		sscanf(buff[0], "%u", &temp.m_sId);
		sscanf(buff[1], "%s", temp.m_cId);
		sscanf(buff[2], "%lf", &temp.m_score);
		ReadFileToDataSystem();
		SetScore(ModifyOptCourse, &temp, &temp);
		free(temp.m_cId);
		courseUI.m_editorUIVisible = 1;
		WriteFileFromOptCourseList("../DataSystem/Data/OptCourseTable.txt", &dataSystem.m_optCourseTable, "w");
		ReadFileToEditor("../DataSystem/Data/OptCourseTable.txt", &courseUI.m_textData, &courseUI.m_editor);
		courseUI.m_setScoreUIVisible = 0;
	}
}

void CourseEditorUIDisplay()
{
	DrawEditor(TextStringWidth("纵览课程信息") + 1, 1.0, 7.5, 5.5, &courseUI.m_editor);
}
