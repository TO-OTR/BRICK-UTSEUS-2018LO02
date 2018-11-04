#pragma once

#include "body.h"
class Brick :
	public Body
{
public:
	Brick(const Box &box, const Position &position, const string &pix);
	~Brick(void);
	void update();
	void setRate(double v);
	void setHardness(int n);
	void getRate(double &rate);
	void getSpeed(double &x, double &y, const Position &pos);
	void collide();
private:
	bool firstUpdate;
	double rate;
	int hardness;
};

