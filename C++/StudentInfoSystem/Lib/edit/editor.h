#pragma once

#include "imgui.h"
#include "graphics.h"
#include "extgraph.h"
#include "..//error.h"
#include "mystring.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Editor
{
	mystring m_srcData; 
	char** m_formateData;
	int m_lines;
}Editor;


mystring GetTextData(const Editor* editor);
void SetSrcData(Editor* edit, const char* text);
void DrawEditor(double x, double y, double w, double h, const Editor * editor);
int SplitLine(const char* str, char *** formateData, int * lines);
