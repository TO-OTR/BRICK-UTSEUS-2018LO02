#include "pch.h"
#include "GameConsole.h"


GameConsole::GameConsole(void)
{
	barre=nullptr;
}


GameConsole::~GameConsole(void)
{
}
void GameConsole::setBarre(Barre &_barre)
{
	barre=&_barre;
}
void GameConsole::onKeyPressed(WORD keyCode)
{
	if(keyCode=='a' || keyCode=='A' ||keyCode==37 ){
		barre->LeftMove();
	}
	if(keyCode=='D' || keyCode=='D' || keyCode == 39){
		barre->RightMove();
	}
}