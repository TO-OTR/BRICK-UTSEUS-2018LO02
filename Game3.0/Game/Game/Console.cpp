#include "pch.h"
#include "console.h"
using namespace std;

const _TCHAR *console_exception::what() const {
	return info;
}

Console::Console() {
	hScreenBuffer = GetStdHandle(STD_OUTPUT_HANDLE);
	input = GetStdHandle(STD_INPUT_HANDLE);
	if (hScreenBuffer == INVALID_HANDLE_VALUE) {
		throw console_exception(_T("Can't get screen handle"));
	}
	GetConsoleScreenBufferInfo(hScreenBuffer, &screenInfo);
	//set input and output codepage to 437 (https://en.wikipedia.org/wiki/Code_page_437)
	originalConsoleCP = GetConsoleCP();
	//	cout << "Original Console CP: " << originalConsoleCP <<endl;
	SetConsoleCP(437);
	originalConsoleOutputCP = GetConsoleOutputCP();
	SetConsoleOutputCP(437);
	//clear the screen
	clear();
	//start the event thread
	RegisterWaitForSingleObject(&wait,input,EventRoutine,this,INFINITE,0);

}

Console::~Console() {
	// restore l'état initial de la console (couleur,...)
	SetConsoleTextAttribute(hScreenBuffer, screenInfo.wAttributes);
	SetConsoleCP(originalConsoleCP);
	SetConsoleOutputCP(originalConsoleOutputCP);
	//stop the event thread
	UnregisterWait(wait);
}

VOID CALLBACK Console::EventRoutine(PVOID lpParam, BOOLEAN TimerOrWaitFired) {
	//read events
	
	Console *console = reinterpret_cast<Console *>(lpParam);

	INPUT_RECORD irInBuf[4];
	DWORD cNumRead;
	if (ReadConsoleInput(console->input, irInBuf, 4, &cNumRead)) {
		for (DWORD i = 0; i < cNumRead; i++) {
			if (irInBuf[i].EventType == KEY_EVENT) { //only handle key event
				if (irInBuf[i].Event.KeyEvent.bKeyDown) { //key pressed
					console->onKeyPressed(irInBuf[i].Event.KeyEvent.wVirtualKeyCode);
				}
			}
		}
	}
}

void Console::set_title(LPCTSTR s) {
	SetConsoleTitle(s);
}

void Console::set_pen_color(color c) {
	switch (c) {
	case default_color:
		SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	case red:
		SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;
	case green:
		SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		break;
	case blue:
		SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		break;
	case yellow:
		SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		break;
	case white:
		SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		break;
	case black:
		SetConsoleTextAttribute(hScreenBuffer, 0);
		break;
	case dark_red:
		SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_RED);
		break;
	case dark_green:
		SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_GREEN);
		break;
	case dark_blue:
		SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_BLUE);
		break;
	case dark_yellow:
		SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_RED | FOREGROUND_GREEN);
		break;
	default:
		throw console_exception(_T("Unknown color in set_cursor_color"));
	}
}

void Console::set_cursor_position(unsigned int x, unsigned int y) {
	COORD p;
	p.X = x;
	p.Y = y;
	SetConsoleCursorPosition(hScreenBuffer, p);
}

void Console::set_hide_cursor() {
	CONSOLE_CURSOR_INFO cci;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleCursorInfo(hConsole, &cci);

	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &cci);
}

void Console::clear() {
	system("CLS");
}

bool Console::set_dimensions(unsigned int width, unsigned int height) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	COORD  coordMax;
	coordMax = GetLargestConsoleWindowSize(hScreenBuffer);
	SHORT w = (SHORT)width, h = (SHORT)height;
	if (h > coordMax.Y) h = coordMax.Y;
	if (w > coordMax.X) w = coordMax.X;
	if (!GetConsoleScreenBufferInfo(hScreenBuffer, &info)) return FALSE;
	/* - hauteur - */
	info.srWindow.Left = 0;
	info.srWindow.Right = info.dwSize.X - 1;
	info.srWindow.Top = 0;
	info.srWindow.Bottom = h - 1;

	if (h < info.dwSize.Y) {
		if (!SetConsoleWindowInfo(hScreenBuffer, TRUE, &info.srWindow)) return FALSE;
		info.dwSize.Y = h;
		if (!SetConsoleScreenBufferSize(hScreenBuffer, info.dwSize)) return FALSE;
	}
	else if (h > info.dwSize.Y) {
		info.dwSize.Y = h;
		if (!SetConsoleScreenBufferSize(hScreenBuffer, info.dwSize)) return FALSE;
		if (!SetConsoleWindowInfo(hScreenBuffer, TRUE, &info.srWindow))
			return FALSE;
	}
	if (!GetConsoleScreenBufferInfo(hScreenBuffer, &info)) return FALSE;

	/* --- largeur - */
	info.srWindow.Left = 0;
	info.srWindow.Right = w - 1;
	info.srWindow.Top = 0;
	info.srWindow.Bottom = info.dwSize.Y - 1;
	if (w < info.dwSize.X) {
		if (!SetConsoleWindowInfo(hScreenBuffer, TRUE, &info.srWindow)) return FALSE;
		info.dwSize.X = w;
		if (!SetConsoleScreenBufferSize(hScreenBuffer, info.dwSize))
			return FALSE;
	}
	else if (w > info.dwSize.X) {
		info.dwSize.X = w;
		if (!SetConsoleScreenBufferSize(hScreenBuffer, info.dwSize)) return FALSE;
		if (!SetConsoleWindowInfo(hScreenBuffer, TRUE, &info.srWindow))
			return FALSE;
	}
	if (!GetConsoleScreenBufferInfo(hScreenBuffer, &info)) return FALSE;
	return TRUE;
}

void Console::put_char(unsigned char c, unsigned int x, unsigned int y) {
	// écrit le caractère c en (x,y)
	set_cursor_position(x, y);
	std::cout << c;
}

void Console::clear(unsigned int x, unsigned int y) {
	set_cursor_position(x, y);
	std::cout << ' ';
}

void Console::put_string(string s, unsigned int x, unsigned int y) {
	// écrit la chaine de caractères s en (x,y),(x+1,y),(x+2,y)...(x+s.length()-1)
	set_cursor_position(x, y);
	std::cout << s;
}

unsigned short Console::getWidth() const {
	return screenInfo.dwSize.X;
}

unsigned short Console::getHeight() const {
	return screenInfo.dwSize.Y;
}
