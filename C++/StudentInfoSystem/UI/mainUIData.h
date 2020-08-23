#pragma once

#include "genlib.h"
#include "imgui.h"
#include "extgraph.h"

#include "..//Lib/String/__string.h"
#include "../DataSystem/DataSystem.h"
#include "CourseUI.h"
#include "FileUI.h"
#include "HelpUI.h"
#include "SearchUI.h"
#include "sortUI.h"
#include "StudentUI.h"

#include <Windows.h>
#include <stdio.h>
#include <string.h>
typedef struct mainUI
{
	bool m_WinVisible;
	bool m_MenuVisible;
	bool m_ToolVisible;
	bool m_StatusVisible;
	bool m_LabelVisible;
	bool m_init;
	mystring m_openFilePath;
	mystring m_saveFilePath;
}MainUI;

typedef enum
{
	menuMain,
	toolMain,
	statusMain,
	labelMain,
}whichMain;

void AllMainUIClose();
void SetMainUIMemberVisible(whichMain which);

void InitMainUI();
void MainLabelDisplay();

void MainMenuDisplay();

void MainToolBarDisplay();

void MainStatusBarDisplay();

void MainUIDisplay();

void InitAllUI();


