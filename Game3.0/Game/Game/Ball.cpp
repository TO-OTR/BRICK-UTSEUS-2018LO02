#include "pch.h"
#include "Ball.h"
#include "Brick.h"
#include "Frame.h"
#include "Barre.h"

Ball::Ball(const Box &box, const Position &position, const string &pix):Body("Ball", box, position, pix)//Body(name,Box(4,4),position, string("■"))
{
	speedX=0;
	speedY=0;
	accX=0;
	accY=0;
	rate=1;
	requestDraw = true;
}


Ball::~Ball(void)
{
}

void Ball::setSpeed(double x, double y)
{
	speedX=x;
	speedY=y;
}
void Ball::setRate(double rate)
{
	this->rate=rate;
}
void Ball::update()
{
	bodyManager->getConsole().set_pen_color(default_color);
	accX+=rate*speedX;
	accY+=rate*speedY;
	Position newPos= prevPosition;
	while(accX>=1.0){
		newPos.x+=1;
		accX-=1;
	}
	while(accX<=-1.0){
		newPos.x-=1;
		accX+=1;
	}
	while(accY>=1.0){
		newPos.y+=1;
		accY-=1;
	}
	while(accY<=-1.0){
		newPos.y-=1;
		accY+=1;
	}
	if(bodyManager==nullptr) return;
	Body *collidingBody=nullptr;
	if(!bodyManager->moveBody(*this, newPos, &collidingBody)){
		if(collidingBody!=nullptr){
			double rateX=1.0;
			double rateY=1.0;
			if(strcmp(collidingBody->getName().c_str(),"Frame")==0){
				Frame* frame=(Frame*)collidingBody;
				frame->getSpeed(speedX,speedY);
				if(frame->isQuit()){
					bodyManager->quit();
				}
			}
			if(strcmp(collidingBody->getName().c_str(),"Brick")==0){
				Brick* brick=(Brick*)collidingBody;
				brick->getRate(rate);
				brick->getSpeed(speedX,speedY,prevPosition);
				brick->collide();
				bodyManager->score += 100;
			}
			if(strcmp(collidingBody->getName().c_str(),"Barre")==0){
				Barre* barre=(Barre*)collidingBody;
				barre->getSpeed(speedX,speedY,prevPosition);
			}
		}
	}
}