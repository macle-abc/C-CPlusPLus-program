#include "FileUI.h"

FileUI fileUI;
extern double winwidth;
extern double winheight;

void allFileUIClose()
{
	fileUI.m_textVisible = 0;
}

void setFileUIVisible(whichFil which)
{
	switch (which)
	{
	case textFil:
		fileUI.m_textVisible = 1;
	default:
		break;
	}
}

void fileUIDisplay()
{
	if (fileUI.m_textVisible)
		fileUIDisplayText(TextStringWidth("×ÝÀÀ¿Î³ÌÐÅÏ¢") + 1, 1.0, 7.5, 5.5);
}

void initFilUI()
{
	int len = fileUI.m_edit.m_lines;
	int i = 0;
	mystring_init(&fileUI.m_edit.m_srcData);
	mystring_init(&fileUI.m_textData);
	fileUI.flag = 1;
	fileUI.m_textVisible = 0;
	fileUI.m_winVisible = 0;
}

void fileUIDisplayText(double x, double y, double w, double h)
{

	if (fileUI.flag != 1)
		initFilUI();
	DrawEditor(x, y, w, h, &fileUI.m_edit);
	
}
