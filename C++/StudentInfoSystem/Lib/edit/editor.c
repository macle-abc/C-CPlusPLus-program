#include "editor.h"

mystring GetTextData(const Editor* editor)
{
	return editor->m_srcData;
}

void SetSrcData(Editor* edit, const char* text)
{
	mystring_init(&edit->m_srcData);
	edit->m_srcData.assign(&edit->m_srcData, text);
	SplitLine(edit->m_srcData.c_str(&edit->m_srcData), &edit->m_formateData, &edit->m_lines);
}


void DrawEditor(double x, double y, double w, double h, const Editor * editor)
{
	unsigned index = 1;
	double fontHeight = GetFontHeight();

	drawRectangle(x, y, w, h, 0);
	for (; index != editor->m_lines + 1; ++index)
	{
		MovePen(x + 0.1, y + h - fontHeight * index);
		DrawTextString(editor->m_formateData[index - 1]);
	}
}

int SplitLine(const char* str, char *** formateData, int * lines)
{
	char* s = "\n";
	char* b_str = (char*)malloc(strlen(str));
	char* b_str_tmp = NULL;
	int cnt = 0;
	char* buf = NULL;
	int i = 0;
	if (NULL == b_str)
	{
		fprintf(stderr, "Don't have enough memory");
		error;
		return 0;
	}
	memcpy(b_str, str, strlen(str));

	b_str_tmp = b_str;
	cnt = 0;
	buf = strstr(b_str, s);
	while (buf != NULL)
	{
		cnt++;
		b_str = buf + strlen(s);
		buf = strstr(b_str, s);
	}
	*formateData = (char**)malloc(sizeof(char*) * cnt);
	if (NULL == *formateData)
	{
		fprintf(stderr, "Don't hava enough memroy");
		error;
		free(b_str);
		b_str = NULL;
		return 0;
	}
	b_str = b_str_tmp;
	buf = strstr(b_str, s);
	while (buf != NULL)
	{
		buf[0] = '\0';
		(*formateData)[i] = b_str;
		b_str = buf + strlen(s);
		buf = strstr(b_str, s);
		i++;
	}
	*lines = cnt;
	return 1;
}
