#include "pch.h"
#include "Brick.h"


Brick::Brick(const Box &box, const Position &position, const string &pix):Body("Brick", box, position, pix)//Body("Brick",Box(8,4),position,"▄▄▄")
{
	rate=1.0;
	hardness=1;
	firstUpdate = true;
}


Brick::~Brick(void)
{
}
void Brick::update()
{
	if(hardness<=0){
		position.x=2;
		position.y=2;
		disabled=true;
		requestDraw=false;
	}
	if (firstUpdate) {
		requestDraw = true;
		firstUpdate = false;
	}
	if (hardness <= 0) {
		bodyManager->getConsole().set_pen_color(black);
	}
	else if(hardness==1){
		bodyManager->getConsole().set_pen_color(red);
	}
	else{
		bodyManager->getConsole().set_pen_color(blue);
	}
}
void Brick::setRate(double v)
{
	rate=v;
}
void Brick::setHardness(int n)
{
	hardness=n;
}

void Brick::getRate(double &rate)
{
	rate=this->rate;
}
void Brick::getSpeed(double &x, double &y, const Position &pos)
{
	int disX;
	int disY;
	Position p(0,0);
	p=prevPosition;
	disX=pos.x-p.x;
	disY=pos.y-p.y;
	if (disX == 0) {
		y = -y;
		return;
	}
	if (disY == 0) {
		x = -x;
		return;
	}
	x = -x;
	y = -y;
}

void Brick::collide()
{
	hardness--;
	requestDraw = true;
}