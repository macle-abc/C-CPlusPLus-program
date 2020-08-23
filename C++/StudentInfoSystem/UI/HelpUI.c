#include "HelpUI.h"

void ShowAbout()
{
	MessageBox((HWND)0, (LPCSTR)About(), (LPCSTR)"关于", (UINT)64);
}

void ShowApproach()
{
	MessageBox((HWND)0, (LPCSTR)Approach(), (LPCSTR)"使用方法", (UINT)64);
}
