#pragma once

#include "body.h"
class Ball :
	public Body
{
public:
	Ball(const Box &box, const Position &position, const string &pix);
	~Ball(void);
	void update();
	void setSpeed(double x, double y);
	void setRate(double rate);
private:
	double speedX;
	double speedY;
	double rate;
	double accX;
	double accY;
};

