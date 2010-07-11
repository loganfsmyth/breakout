#include "Ball.h"

Ball::Ball(int x, int y){
	
	textured = false;
	
	timer = new Timer();
	bool stat = timer->init();
	if(!stat) printf("Ball: Failed to Init TImer\n");
		
	
		
	this->x = x;
	this->y = y;
	
	srand ( time(NULL) );
	
	int dir = rand()%2;
	if(dir == 0) dir = -1;
	
//	dir = 0;
	dir = -1;
	
	xVel = 0.2*dir;
	yVel = -0.2;
}

void Ball::enableTexture(){
	textured = true;
}
void Ball::disableTexture(){
	textured = false;
}
void Ball::render(){
	
	glColor3f(0.9,0.1,0.1);
	glTranslatef(x, y, 0);
	glBegin(GL_QUADS);
		glVertex2f(-BALL_RADIUS,-BALL_RADIUS);
		if(textured) glTexCoord2f(0.15, 0.15);
		glVertex2f(-BALL_RADIUS, BALL_RADIUS);
		if(textured) glTexCoord2f(0.15, 0.85);
		glVertex2f(BALL_RADIUS, BALL_RADIUS);
		if(textured) glTexCoord2f(0.85,0.85);
		glVertex2f(BALL_RADIUS, -BALL_RADIUS);
		if(textured) glTexCoord2f(0.85, 0.15);
	glEnd();
}
void Ball::move(){
	
	if(!timer->isRunning()){
		timer->start();
		printf("Starting\n");
	}
	else{
		x += xVel*timer->getTime();
		y += yVel*timer->getTime();
		
		timer->start();
	}
}

void Ball::invertXVel(){
	xVel *= -1;
}
void Ball::invertYVel(){
	yVel *= -1;
}

int Ball::getX(){
	return x;
}
int Ball::getY(){
	return y;
}
int Ball::getR(){
	return BALL_RADIUS-BALL_BORDER;
}
void Ball::setX(int x){
	this->x = x;
}
void Ball::setY(int y){
	this->y = y;
}

Rect* Ball::getRect(){
	int r = (BALL_RADIUS-BALL_BORDER);
	return new Rect(x-r,y-r,r*2,r*2);
}

bool Ball::movingNW(){
	if(xVel < 0 && yVel < 0) return true;
	else return false;
}
bool Ball::movingSW(){
	if(xVel < 0 && yVel > 0) return true;
	else return false;
}
bool Ball::movingNE(){
	if(xVel > 0 && yVel < 0) return true;
	else return false;
}
bool Ball::movingSE(){
	if(xVel > 0 && yVel > 0) return true;
	else return false;
}

Ball::~Ball(){
	delete timer;
}

