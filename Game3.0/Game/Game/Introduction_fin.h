#pragma once
#include "pch.h"
#include <iostream>
#include "BodyManager.h"
#include "Ball.h"
void Gamestart()
{
	std::cout << "							Introduction						  " << "\n"
		<< "					  This game is called 'Happy Ball'.		          " << "\n"
		<< "			You are allowed to use controler left and right to control the bar    " << "\n"
		<< "			and use mouse left click to stop and the blank to continue.           " << "\n"
		<< "			There will be three kinds of bricks, blue ones will break after 2 kick" << "\n"
		<< "			while the red ones will break after one kick. On the same time, you may" << "\n"
		<< "			luckly hit the speedup brick or slowdown brick as will. They don't have" << "\n"
		<< "			special colors. Each time you hit a brick you will get 100points,if you" << "\n"
		<< "			drop below de bar, you will lose the game.                            " << std::endl;



	system("pause");

	std::cout << "																	" << "\n"
		<< "																	" << "\n"
		<< "			   NOW IF YOU ARE READY						" << "\n"
		<< "			   PRESS ANT BUTTON TO START YOU ADVENTURE		        " << std::endl;

	system("pause");
}

