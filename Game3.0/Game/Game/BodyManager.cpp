#include "pch.h"
#include "BodyManager.h"
#include "Body.h"
#include <algorithm>
#include "stdio.h"
bool BodyManager::addBody(Body &body) {
	if (fitBody(body, body.position)) {
		bodies.push_back(&body);
		body.bodyManager = this;
		return true;
	} else return false;
}

bool BodyManager::moveBody(Body &body, const Position &position, Body **collidingBody) {
	if (find(bodies.begin(), bodies.end(), &body) == bodies.end()) return false; //body not found
	if (fitBody(body, position, collidingBody)) {
		body.position = position;
		return true;
	} else return false;
}

bool BodyManager::fitBody(const Body &body, const Position &position, Body **collidingBody) {
	if ((position.x + body.box.width > worldBox.width) || (position.y + body.box.height > worldBox.height)) {
		return false; //doesn't fit in the world
	}
	//for (auto it = bodies.begin(); it != bodies.end(); ++it) {
		//if ((*it) == &body) continue; //do not check with itself
		//if (collide(**it, body.box, position)) {
			//cerr << "collision between body " << (*it)->name << " and body " << body.name;
			//if (collidingBody) *collidingBody = *it;
	for (auto it : bodies) {
		if ((it) == &body) continue; //do not check with itself
		if (collide(*it, body.box, position)) {
			//cerr << "collision between body " << (*it)->name << " and body " << body.name;
			if (collidingBody) *collidingBody = it;
			return false;
		}
	}
	if (collidingBody) *collidingBody = nullptr;
	return true;
}

bool BodyManager::collide(const Body & body, const Box &box, const Position &position) { //collision
	if (body.disabled) return false;
	if ((position.x + box.width <= body.position.x) || (body.position.x + body.box.width <= position.x))
		return false;
	else {
		if ((position.y + box.height <= body.position.y) || (body.position.y + body.box.height <= position.y))
			return false;
		else return true;
	}
}

void BodyManager::run() {
	for (auto it = bodies.begin(); it != bodies.end(); ++it) {
		(*it)->draw();
	}
	getConsole().set_hide_cursor();
	while (!exit) {
		//getConsole().set_pen_color(white);
		for (auto it = bodies.begin(); it != bodies.end(); ++it) {
			(*it)->update();
			if ((*it)->requestDraw || ((*it)->prevPosition != (*it)->position)) {
				(*it)->draw();
			}
		}
		getConsole().set_pen_color(white);
		char scorestr[20];
		sprintf_s(scorestr,18,"%d",score);
		getConsole().put_string(scorestr,90,3);
		getConsole().set_hide_cursor();
		Sleep(10); //relax cpu (should use a periodic timer set with CreateTimerQueueTimer instead, but too complex for this project)
	}
}
