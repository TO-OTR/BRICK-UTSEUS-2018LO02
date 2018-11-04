
#ifndef _CONSOLES
#define _CONSOLES

#include <Windows.h>
#include <string>
#include <tchar.h>
#include <strsafe.h>
#include <iostream>
#include <exception>

enum color { default_color, blue, yellow, red, green, white, black, dark_blue, dark_yellow, dark_red, dark_green };

//IMPORTANT: console is set up to use codepage 437 (pseudo-graphical character set that should work on any computer worldwide)
//See (https://en.wikipedia.org/wiki/Code_page_437) for the detail of the characters available
class Console { 
public:
	Console();
	~Console();
	void set_title(LPCTSTR s); //set window title
	bool set_dimensions(unsigned int width, unsigned int height); //change console size
	void set_cursor_position(unsigned int x, unsigned int y);
	void set_hide_cursor();
	void set_pen_color(color c); //change characters color
	void clear(unsigned int x, unsigned int y); //blank character at given position
	void clear(); //blank the whole screen
	void put_char(unsigned char c, unsigned int x, unsigned int y); //write character c at given position. A character is 1 byte wide and taken from codepage 437
	void put_string(std::string, unsigned int x, unsigned int y); //write the string s at given position. Characters are 1 byte wide and taken from codepage 437
	virtual void onKeyPressed(WORD keyCode) {}; //does nothing by default, must be overloaded in subclass
	unsigned short getWidth() const;
	unsigned short getHeight() const;
private:
	HANDLE hScreenBuffer;
	HANDLE input;
	DWORD originalConsoleMode;
	CONSOLE_SCREEN_BUFFER_INFO screenInfo;
	UINT originalConsoleCP;
	UINT originalConsoleOutputCP;
	//event thread
	HANDLE wait;
	static VOID CALLBACK EventRoutine(PVOID lpParam, BOOLEAN TimerOrWaitFired);
};


class console_exception {
	_TCHAR info[64];
public:
	console_exception(LPCTSTR s) {
		StringCchCopy(info, 64, s);
	}
	const _TCHAR* what() const;
};

#endif
