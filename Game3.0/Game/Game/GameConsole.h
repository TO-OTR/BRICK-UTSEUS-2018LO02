#pragma once
#include "console.h"
#include "Barre.h"
class GameConsole :
	public Console
{
public:
	GameConsole(void);
	~GameConsole(void);
	void onKeyPressed(WORD keyCode);
	void setBarre(Barre &_barre);
private:
	Barre *barre;
};

