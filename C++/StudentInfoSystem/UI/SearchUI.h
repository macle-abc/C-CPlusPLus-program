#pragma once

#include "genlib.h"
#include "imgui.h"
#include "graphics.h"
#include "../DataSystem//DataSystem.h"
#include "SearchAssistance.h"
#include "..//Lib/edit/editor.h"


typedef struct SearchUI
{
	bool m_studentUIVisible;
	bool m_courseUIVisible;
	bool m_scoreUIVisible;
	bool m_collectUIVisible;
	bool m_editorUIVisible;
	mystring m_textData;
	Editor m_editor;
}SearchUI;

typedef enum
{
	studentSearch,
	courseSearch,
	scoreSearch,
	collectSearch,
	editorSearch
}whichSea;

void InitSearchUI();
void AllSearchUIClose();
void SetSearchMemberUIVisible(whichSea which);
void SearchUIDisplay();
void SearchStudentUIDisplay();
void SearchCourseUIDisplay();
void SearchScoreUIDisplay();
void SearchCollectUIDisplay();
void SearchEditorUIDisplay();
