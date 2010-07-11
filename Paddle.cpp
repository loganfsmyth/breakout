#include "Paddle.h"

Paddle::Paddle(double x, double y, double w):DynamicObject(x,y,w,PADDLE_HEIGHT, 0.0, 0.0, 0.0, 0.0, PADDLE_MAX_VELOCITY, PADDLE_MAX_VELOCITY){
	moveLeft = false;
	moveRight = false;
}
void Paddle::move(){
	if(moveLeft == moveRight){
		xAcc = 0.0;
		xVel = 0.0;
	}
	else if(moveLeft){
		xAcc = -PADDLE_ACCELERATION;
	}
	else if(moveRight){
		xAcc = PADDLE_ACCELERATION;
	}
	DynamicObject::move();
}


void Paddle::setMoveLeft(bool status){
	moveLeft = status;
}
void Paddle::setMoveRight(bool status){
	moveRight = status;
}
bool Paddle::movingRight(){
	if(moveRight == moveLeft) return false;
	return moveRight;
}
bool Paddle::movingLeft(){
	if(moveRight == moveLeft) return false;
	return moveLeft;
}

void Paddle::render(){
	
	glLoadIdentity();
	glColor3f(0.9,0.1,0.1);
	glTranslatef(x, y, 0);
	
	bindTexture();
	
	glBegin(GL_QUADS);
		if(isTextured()) glTexCoord2f(0.0, 0.0);
		glVertex2f(0,0);
		if(isTextured()) glTexCoord2f(0.0, 1.0);
		glVertex2f(0, h);
		if(isTextured()) glTexCoord2f(1.0,1.0);
		glVertex2f(w, h);
		if(isTextured()) glTexCoord2f(1.0, 0.0);
		glVertex2f(w, 0);
	glEnd();
		
	unbindTexture();
}



