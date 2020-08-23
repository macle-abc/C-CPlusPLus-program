float arr[100];
void Init()
{
	for (int i = 0; i != 100; ++i)
	{
		arr[i] = (float)(100 - i);
	}
}

POINT temp;
void DrawPoint(int x, int y)
{
	for (int j = 0; j != 3; ++j)
		for (int i = 0; i != 3; ++i)
			SetPixel(g_gf->m_hdc, x + i, y + j, RGB(255, 0, 0));
}

bool UI()
{
	static HelpSnack s(3, 5, 6, 10, 6, 15); //static HelpSnack s也行设置了默认值
    //g_gf->ClearBg();
	GetCursorPos(&temp);
	ScreenToClient(g_gf->m_hWnd, &temp);
	s.SnackMove(arr, sizeof(arr) / sizeof(float), (float)temp.x, (float)temp.y);
	for (int i = 0; i < sizeof(arr) / sizeof(float); i += 2)
	{
		DrawPoint(lround(arr[i]), lround(arr[i + 1]));
	}
    //g_gf->FlushDraw();
	return 0;
}
