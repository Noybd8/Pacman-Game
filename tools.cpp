#include "tools.h"
enum DIRECTION { UP, LEFT, RIGHT, DOWN };
void gotoxy(int x, int y) // we changed that the x will be the rows and the y will be the colums.
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	std::cout.flush();
	dwCursorPosition.X = y;
	dwCursorPosition.Y = x;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}
char getKey()
{
	char KeyStroke = _getch();
	if (KeyStroke == 0 || KeyStroke == -32)
		KeyStroke = _getch();
	return (KeyStroke);
}
