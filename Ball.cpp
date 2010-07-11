#include "Ball.h"

Ball::Ball(double x, double y):DynamicObject(x,y,BALL_RADIUS*2,BALL_RADIUS*2,BALL_START_VELOCITY/2,-BALL_START_VELOCITY){
	
}
void Ball::render(){
	
	glLoadIdentity();
	glColor3f(0.9,0.1,0.1);
	glTranslatef(x, y, 0);
	
	glBegin(GL_QUADS);
		glVertex2f(0,0);
		if(isTextured()) glTexCoord2f(0.15, 0.15);
		glVertex2f(0, w);
		if(isTextured()) glTexCoord2f(0.15, 0.85);
		glVertex2f(h, w);
		if(isTextured()) glTexCoord2f(0.85,0.85);
		glVertex2f(h, 0);
		if(isTextured()) glTexCoord2f(0.85, 0.15);
	glEnd();
}

