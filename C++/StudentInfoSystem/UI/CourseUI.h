#pragma once

#include "genlib.h"
#include "imgui.h"
#include "graphics.h"
#include "../DataSystem/Student.h"
#include "..//UI//CourseAssistance.h"
#include "../DataSystem//DataSystem.h"

typedef struct CourseUI
{
	bool m_addRecordUIVisible;
	bool m_removeRecordUIVisible;
	bool m_modifyRecordUIVisible;
	bool m_setScoreUIVisible;
	bool m_editorUIVisible;
	Editor m_editor;
	mystring m_textData;
}CourseUI;

typedef enum 
{
	addRecordCourse,
	removeRecordCourse,
	modifyRecordCourse,
	setScoreCourse,
	editorCourse
}whichCou;

void InitCourseUI();
void AllCourseUIClose();
void SetCourseUIMemberVisible(whichCou which);
void CourseUIDisplay();
void CourseAddRecordUIDisplay();
void CourseRemoveRecordDisplay();
void CourseModifyRecordUIDisplay();
void CourseSetScoreUIDisplay();
void CourseEditorUIDisplay();
