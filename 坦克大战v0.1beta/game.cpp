#include "game.h"
#include <Windows.h>
#include <conio.h>
#include <iostream>

// 定位打印字符
void PrintChar(int Wide, int High, const char* pszChar, int color) {
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);

	COORD loc;
	loc.X = Wide * 2;
	loc.Y = High;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);
	std::cout << pszChar;
}