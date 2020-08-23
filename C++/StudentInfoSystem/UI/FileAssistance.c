#include "FileAssistance.h"

mystring text;
void readToTemp(mystring* des, const char* path)
{
	FILE* file = fopen(path, "r");
	if (NULL == file)
	{
		fprintf(stderr, "Can't open file!");
		return;
	}
	des->fgetline(des, file, EOF);
	fclose(file);
}

void saveFromTemp(mystring* temp, const char* path)
{
	FILE* file = fopen(path, "w");
	char ch = 0;
	if (NULL == file)
	{
		fprintf(stderr, "Can't open file!");
		return;
	}
	fputs(temp->c_str(temp), file);
	fclose(file);
}

void clickOpen()
{
	mystring_init(&text);
	readToTemp(&text, GetOpenFilePath());
}

void clickSave()
{
	saveFromTemp(&text, GetSaveFilePath());
}
