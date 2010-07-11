#include "Ball.h"

Ball::Ball(double x, double y):DynamicObject(x,y,BALL_RADIUS*2,BALL_RADIUS*2,BALL_START_VELOCITY,-BALL_START_VELOCITY){
	textured = false;
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
		glVertex2f(0,0);
		if(textured) glTexCoord2f(0.15, 0.15);
		glVertex2f(0, w);
		if(textured) glTexCoord2f(0.15, 0.85);
		glVertex2f(h, w);
		if(textured) glTexCoord2f(0.85,0.85);
		glVertex2f(h, 0);
		if(textured) glTexCoord2f(0.85, 0.15);
	glEnd();
}
