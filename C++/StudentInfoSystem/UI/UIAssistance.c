#include "UIAssistance.h"
#include <Windows.h>

char* dirPath = "../DataSystem/Data/";
extern FileUI fileUI;
char* GetOpenFilePath()
{

	OPENFILENAME ofn = { 0 };
//	TCHAR strFilename[MAX_PATH] = { 0 };//用于接收文件名
	TCHAR* strFilename = (TCHAR*)malloc(MAX_PATH);
	if (NULL == strFilename)
	{
		fprintf(stderr, "Don't have enough memory!");
		error;
		return NULL;
	}
	memset(strFilename, 0, MAX_PATH);
open:
	ofn.lStructSize = sizeof(OPENFILENAME);//结构体大小
	ofn.hwndOwner = NULL;//拥有着窗口句柄，为NULL表示对话框是非模态的，实际应用中一般都要有这个句柄
	ofn.lpstrFilter = TEXT("文本文件\0*.txt\0\0");//设置过滤
	ofn.nFilterIndex = 1;//过滤器索引
	ofn.lpstrFile = strFilename;//接收返回的文件名，注意第一个字符需要为NULL
	ofn.nMaxFile = strlen(strFilename) + 1;//缓冲区长度
	ofn.lpstrInitialDir = NULL;//初始目录为默认
	ofn.lpstrTitle = TEXT("请选择一个文件");//使用系统默认标题留空即可
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;//文件、目录必须存在，隐藏只读选项
	if (GetOpenFileName(&ofn))
	{
		return strFilename;
	}
	else {
		MessageBox(NULL, TEXT("请选择一个文件"), NULL, MB_ICONERROR);
		goto open;
	}
}

char* GetSaveFilePath()
{
	OPENFILENAME ofn = { 0 };
//	TCHAR strFilename[MAX_PATH] = { 0 };//用于接收文件名
	TCHAR* strFilename = (TCHAR*)malloc(MAX_PATH);
	if (NULL == strFilename)
	{
		fprintf(stderr, "Don't have enough memory!");
		error;
		return NULL;
	}
save:
	ofn.lStructSize = sizeof(OPENFILENAME);//结构体大小
	ofn.hwndOwner = NULL;//拥有着窗口句柄，为NULL表示对话框是非模态的，实际应用中一般都要有这个句柄
	ofn.lpstrFile = strFilename;//接收返回的文件名，注意第一个字符需要为NULL
	ofn.nMaxFile = sizeof(strFilename);//缓冲区长度
	ofn.lpstrInitialDir = NULL;//初始目录为默认
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;//目录必须存在，覆盖文件前发出警告
	ofn.lpstrTitle = TEXT("保存到");//使用系统默认标题留空即可
	ofn.lpstrDefExt = TEXT("txt");//默认追加的扩展名
	if (GetSaveFileName(&ofn))
	{
		return strFilename;
	}
	else
	{
		MessageBox(NULL, TEXT("请输入一个文件名"), NULL, MB_ICONERROR);
		goto save;
	}
}

void ReadFileToEditor(const char* filePath, mystring* textData, Editor* editor)
{
	FILE* file = fopen(filePath, "r");
	char* buff = malloc(1024 * 1024);
	if (NULL == file)
	{
		fprintf(stderr, "Can't open file");
		return;
	}
	textData->fgetline(textData, file, EOF);
	fclose(file);
	strcpy(buff,textData->c_str(textData));
	editor->m_srcData.assign(&editor->m_srcData, buff);
	SplitLine(editor->m_srcData.c_str(&editor->m_srcData), &editor->m_formateData, &editor->m_lines);
}

void WriteFileFromFileUI(const char* filePath)
{
	FILE* file = fopen(filePath, "w");
	char *buff = malloc(strlen(fileUI.m_edit.m_srcData.c_str(&fileUI.m_edit.m_srcData)));
	unsigned length = 0;
	unsigned index = 0;
	strcpy(buff, fileUI.m_edit.m_srcData.c_str(&fileUI.m_edit.m_srcData));
	length = strlen(buff);
	if (NULL == file)
	{
		fprintf(stderr, "Can't open file!");
		return;
	}
		while (index != length)
	{
		fputc(buff[index], file);
		++index;
	}
	fclose(file);
}

unsigned  GetFileLines(const char* filePath)
{
	FILE* fp;
	unsigned flag = 0, file_row = 0, count = 0;
	if ((fp = fopen(filePath, "r")) == NULL)
		return 0;
	while (!feof(fp))
	{
		flag = fgetc(fp);
		if (flag == '\n')
			count++;
	}
	file_row = count + 1; //加上最后一行
	fclose(fp);
	return file_row;
}


unsigned GetStudentRecords()
{	
	char filePath[128] = "";
	unsigned lines = 0;
	strcat(filePath, dirPath);
	strcat(filePath, "StudentTable.txt");
	lines =  GetFileLines(filePath);
	return lines > 0 ? lines - 2 : 0;
}

unsigned GetCourseRecords()
{
	char filePath[128] = "";
	unsigned lines = 0;
	strcat(filePath, dirPath);
	strcat(filePath, "CourseTable.txt");
	lines = GetFileLines(filePath);
	return lines > 0 ? lines - 2 : 0;
}

unsigned GetOptCourseRecords()
{
	char filePath[128] = "";
	unsigned lines = 0;
	strcat(filePath, dirPath);
	strcat(filePath, "OptCourseTable.txt");
	lines = GetFileLines(filePath);
	return lines > 0 ? lines - 2 : 0U;
}
