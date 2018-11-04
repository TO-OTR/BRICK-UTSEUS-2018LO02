#include "pch.h"
#include "Barre.h"


Barre::Barre(const Box &box, const Position &position, const string &pix):Body("Barre", box, position, pix)//Body("Barre",Box(16,4),position,"╔══╦")
{
	diffMove=0;
}


Barre::~Barre(void)
{
}

void Barre::setSpeed(double s)
{
	speed=s;
}
void Barre::LeftMove()
{
	diffMove-=speed;
}
void Barre::RightMove()
{
	diffMove+=speed;
}
void Barre::update()
{
	bodyManager->getConsole().set_pen_color(default_color);
	Position newPos=position;
	while(diffMove>=1.0){
		newPos.x+=1;
		diffMove-=1;
	}
	while(diffMove<=-1.0){
		newPos.x-=1;
		diffMove+=1;
	}
	if(bodyManager==nullptr) return;
	Body *collidingBody=nullptr;
	bodyManager->moveBody(*this, newPos, &collidingBody);
}

void Barre::getSpeed(double &x, double &y, const Position &pos)
{
	int disX;
	disX=pos.x-prevPosition.x;
	if(disX==0){
		y=-0.05;
		x=-0.05;
		return;
	}
	if(disX==1 || disX==2){
		y=-0.1;
		x=0.0;
		return;
	}
	if(disX==3){
		y=-0.05;
		x=0.05;
		return;
	}
	
}
