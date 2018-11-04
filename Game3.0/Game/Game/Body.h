#ifndef _BODY
#define _BODY

#include "BodyManager.h"  // car utilisation de Box
#include <string>
using namespace std;

//class BodyManager;
struct Box;
struct Position;

class Body {
	friend class BodyManager;
public:
	Body(const string &name, const Box &box, const Position &position, const string &pix) :name(name), box(box), prevPosition(position), position(position),
		pix(pix), disabled(false), requestDraw(false), bodyManager(nullptr) {
		if (pix.size() != box.height*box.width) throw runtime_error("pix string size must fit box size");
	}
	virtual void update() {};
	void draw();
	bool disabled; //disabled bodies are not checked for collisions
	bool requestDraw; //force drawing at next tick
	inline const string &getName() const { return name; };
	inline const Position &getPosition() const { return position; };
	const Box &getBox() const { return box; };
protected:
	const string name;
	Box box;
	Position prevPosition;
	Position position;
	string pix;
	BodyManager *bodyManager; //set when the body is added by a bodyManager
};

#endif //_BODY
