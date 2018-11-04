#pragma once

#include "body.h"
class Frame :
	public Body
{
public:
	Frame(const Box &box, const Position &position, const string &pix);
	~Frame(void);
	void setRate(double x, double y);
	void getSpeed(double &x, double &y);
	inline void setQuit(bool flag){ quit = flag; };
	inline bool isQuit(){ return quit; };
	void update();
private:
	double rateX;
	double rateY;
	bool quit;
};

