#pragma once

#include "genlib.h"
#include "imgui.h"
#include "graphics.h"
#include "../DataSystem/Student.h"
#include "..//UI//StudentAssistance.h"
#include "../DataSystem//DataSystem.h"
//typedef struct StudentAddUI
//{
//	Student m_data;
//
//}StudentAddUI;
//
//typedef struct StudentRmUI
//{
//	unsigned m_id;
//	string m_name;
//	unsigned m_class;
//	string m_major;
//}StudentRmUI;
//
//typedef struct StudentMvUI
//{
//	unsigned m_id;
//	string m_name;
//}StudentMvUI;
//
//typedef struct StudentSetUI
//{
//	unsigned m_sId;
//	string m_cId;
//	double score;
//}StudentSetUI;

typedef struct StudentUI
{
	//bool m_winVisible;
	bool m_addRecordUIVisible;
	//StudentAddUI m_addUI;
	bool m_removeRecordUIVisible;
	//StudentRmUI m_rmUI;
	bool m_mvUIVisible;
	//StudentMvUI m_mvUI;
	bool m_setUIVisible;
	//StudentSetUI m_setUI;
	Editor m_edit;
	bool m_editVisible;
	bool m_init;
	mystring m_text;
}StudentUI;

typedef enum
{
	addStu,
	rmStu,
	mvStu,
	setStu,
	textStu
}whichStu;

void allStuUIClose();
void setStuUIVisible(whichStu which);
void initStuUI();
void studentUIDisplay();
void StudentUIDrawAddUI();
void StudentUIDrawRmUI();
void StudentUIDrawMvUI();
void StudentUIDrawSetUI();
