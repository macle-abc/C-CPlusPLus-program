#pragma once
#pragma once

#include "genlib.h"
#include "SortAssistance.h"
#include "genlib.h"
#include "imgui.h"
#include "graphics.h"
#include "../DataSystem//DataSystem.h"
#include "..//Lib/edit/editor.h"
#include "mainUIData.h"
#include "../Lib/error.h"

typedef struct SortUI
{
	bool m_scoreUIVisible;
	bool m_studentIdUIVisible;
	bool m_studentNameUIVisible;
	bool m_saveUIVisible;
	bool m_editorUIVisible;
	mystring m_textData;
	Editor m_editor;
}SortUI;

typedef enum
{
	editorSort,
	scoreSort,
	studentIdSort,
	studentNameSort,
	saveSort
}whichSor;

void InitSortUI();
void AllSortUIClose();
void SetSortMemberUIVisible(whichSor which);
void SortUIDisplay();
void SortScoreUIDisplay();
void SortStudentIDUIDisplay();
void SortStudentNameUIDisplay();
void SortOutUIDisplay();
void SortSaveUIDisplay();
void SortEditorUIDisplay();
