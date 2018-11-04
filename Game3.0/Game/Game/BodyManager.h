#ifndef _BODY_MANAGER
#define _BODY_MANAGER

#include "pch.h"
#include <vector>
#include <string>
#include "Console.h"
class Body;

using namespace std;

struct Box {
	Box(unsigned short width, unsigned short height):width(width),height(height){}
	unsigned short width;
	unsigned short height;
};

struct Position {
	Position(unsigned short x, unsigned short y):x(x),y(y) {}
	unsigned short x;
	unsigned short y;
	bool operator!=(const Position &position) { return (x != position.x) || (y != position.y); }
};

class BodyManager {
public:
	BodyManager(const Box &worldBox, Console &console) :exit(false), worldBox(worldBox), console(console), score(0){};
	bool addBody(Body &body);
	//move body. Return false if not possible (collision)
	bool moveBody(Body &body, const Position &position, Body **collidingBody=nullptr);
	//check if the body could fit in the given position. Return false if not (collision)
	bool fitBody(const Body &body, const Position &position, Body **collidingBody=nullptr);
	void run();
	inline void quit() { exit = true; };
	inline Console &getConsole() { return console; };
	int score;
private:
	bool collide(const Body &body1, const Box &box, const Position &position);
	vector<Body *> bodies;
	Box worldBox;
	Console &console;
	bool exit;
};

#endif // !_BODY_MANAGER

