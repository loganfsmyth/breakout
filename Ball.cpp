#include "Ball.h"

Ball::Ball(double x, double y):DynamicObject(x,y,BALL_RADIUS*2,BALL_RADIUS*2,BALL_START_VELOCITY,-BALL_START_VELOCITY){
	
}
void Ball::render(){
	
	glLoadIdentity();
	glColor3f(0.9,0.1,0.1);
	glTranslatef(x-BALL_BORDER, y-BALL_BORDER, 0);
	
	bindTexture();
	
	glBegin(GL_QUADS);
		if(isTextured()) glTexCoord2f(0.0, 0.0);
		glVertex2f(0,0);
		if(isTextured()) glTexCoord2f(0.0, 1.0);
		glVertex2f(0, w+BALL_BORDER*2);
		if(isTextured()) glTexCoord2f(1.0,1.0);
		glVertex2f(h+BALL_BORDER*2, w+BALL_BORDER*2);
		if(isTextured()) glTexCoord2f(1.0, 0.0);
		glVertex2f(h+BALL_BORDER*2, 0);
	glEnd();
		
	unbindTexture();
}

