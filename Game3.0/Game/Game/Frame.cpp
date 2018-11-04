#include "pch.h"
#include "Frame.h"


Frame::Frame(const Box &box, const Position &position, const string &pix):Body("Frame",box,position,pix)
{
	rateX=1.0;
	rateY=1.0;
	quit=false;
}


Frame::~Frame(void)
{
}

void Frame::setRate(double x, double y)
{
	rateX=x;
	rateY=y;
}
void Frame::getSpeed(double &x, double &y)
{
	x*=rateX;
	y*=rateY;
}
void Frame::update()
{
	bodyManager->getConsole().set_pen_color(white);
}