#pragma once

#include <iostream>
#include <Windows.h>
using std::cout;

inline void gotoxy(short x, short y)
{
	const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const COORD cursorLoc{x, y};
	cout.flush();

	SetConsoleCursorPosition(hConsole, cursorLoc);
}

inline void setFontSize(short a, short b)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
	lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(hConsole, 0, lpConsoleCurrentFontEx);
	lpConsoleCurrentFontEx->dwFontSize.X = a;
	lpConsoleCurrentFontEx->dwFontSize.Y = b;
	SetCurrentConsoleFontEx(hConsole, 0, lpConsoleCurrentFontEx);
}

inline void setWindowSize(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	//MoveWindow(window_handle, x, y, width, height, redraw_window);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

inline void hidecursor()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConCurInf;

	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = FALSE;

	SetConsoleCursorInfo(hOut, &ConCurInf);
}