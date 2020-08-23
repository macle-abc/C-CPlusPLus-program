#pragma once

#include "genlib.h"
#include "imgui.h"
#include "extgraph.h"
#include "..//Lib/String/__string.h"
#include "..//Lib/edit/editor.h"
#include <Windows.h>

typedef struct FileUI
{
	bool m_textVisible;
	bool m_winVisible;
	mystring m_textData;
	Editor m_edit;
	bool flag;
}FileUI;


typedef enum
{
	textFil
}whichFil;

void allFileUIClose();
void setFileUIVisible(whichFil which);
void fileUIDisplay();
void fileUIDisplayText(double x, double y, double w, double h);
void initFilUI();
