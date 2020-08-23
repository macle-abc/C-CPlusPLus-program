#include "sortUI.h"

SortUI sortUI;
void InitSortUI()
{
	AllSortUIClose();
	mystring_init(&sortUI.m_editor.m_srcData);
	mystring_init(&sortUI.m_textData);
}

void AllSortUIClose()
{
	sortUI.m_saveUIVisible = 0;
	sortUI.m_scoreUIVisible = 0;
	sortUI.m_studentIdUIVisible = 0;
	sortUI.m_studentNameUIVisible = 0;
	sortUI.m_editorUIVisible = 0;
}

void SetSortMemberUIVisible(whichSor which)
{
	switch (which)
	{
	case editorSort:
		sortUI.m_editorUIVisible = 1;
		break;
	case saveSort:
		sortUI.m_saveUIVisible = 1;
		break;
	case scoreSort:
		sortUI.m_scoreUIVisible = 1;
		break;
	case studentIdSort:
		sortUI.m_studentIdUIVisible = 1;
		break;
	case studentNameSort:
		sortUI.m_studentNameUIVisible = 1;
		break;
	default:
		break;
	}
}

void SortUIDisplay()
{
	if (sortUI.m_scoreUIVisible)
		SortScoreUIDisplay();
	if (sortUI.m_studentIdUIVisible)
		SortStudentIDUIDisplay();
	if (sortUI.m_studentNameUIVisible)
		SortStudentNameUIDisplay();
	if (sortUI.m_editorUIVisible)
		SortEditorUIDisplay();
}

void SortScoreUIDisplay()
{
	ReadFileToDataSystem();
	Sort(CompareByScore, optCourse);
	WriteFileFromOptCourseList("../DataSystem/Data/OptCourseTable.txt", &dataSystem.m_optCourseTable, "w");
	ReadFileToEditor("../DataSystem/Data/OptCourseTable.txt", &sortUI.m_textData, &sortUI.m_editor);
	sortUI.m_scoreUIVisible = 0;
	sortUI.m_editorUIVisible = 1;
}

void SortStudentIDUIDisplay()
{
	ReadFileToDataSystem();
	Sort(CompareByStudentID, student);
	WriteFileFromStuList("../DataSystem/Data/StudentTable.txt", &dataSystem.m_studentTable, "w");
	ReadFileToEditor("../DataSystem/Data/StudentTable.txt", &sortUI.m_textData, &sortUI.m_editor);
	sortUI.m_studentIdUIVisible = 0;
	sortUI.m_editorUIVisible = 1;
}

void SortStudentNameUIDisplay()
{
	ReadFileToDataSystem();
	Sort(CompareByStudentName, student);
	WriteFileFromStuList("../DataSystem/Data/StudentTable.txt", &dataSystem.m_studentTable, "w");
	ReadFileToEditor("../DataSystem/Data/StudentTable.txt", &sortUI.m_textData, &sortUI.m_editor);
	sortUI.m_studentNameUIVisible = 0;
	sortUI.m_editorUIVisible = 1;
}

void SortOutUIDisplay()
{
}

void SortSaveUIDisplay()
{
	char path[1024] = { 0 };
	mystring data;
	FILE* file = NULL;
	mystring_init(&data);
	strcpy(path, GetSaveFilePath());
	file = fopen(path, "w");
	data.assign(&data, sortUI.m_textData.c_str(&sortUI.m_textData));
	if (NULL == file)
	{
		data.destroy(&data);
		fprintf(stderr, "Can't open file!");
		error;
		data.destroy(&data);
		return;
	}
	data.write(&data, file);
	fclose(file);
}

void SortEditorUIDisplay()
{
	DrawEditor(TextStringWidth("×ÝÀÀ¿Î³ÌÐÅÏ¢") + 1, 1.0, 7.5, 5.5, &sortUI.m_editor);
}
