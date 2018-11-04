#pragma once

#include "body.h"
class Barre :
	public Body
{
public:
	Barre(const Box &box, const Position &position, const string &pix);
	~Barre(void);
	void update();
	void setSpeed(double s);
	void LeftMove();
	void RightMove();
	void getSpeed(double &x, double &y, const Position &pos);
private:
	double speed;
	double diffMove;
};

