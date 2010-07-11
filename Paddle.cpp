#include "Paddle.h"

Paddle::Paddle(double x, double y, double w):DynamicObject(x,y,w,PADDLE_HEIGHT, 0.0, 0.0, 0.0, 0.0, PADDLE_MAX_VELOCITY, PADDLE_MAX_VELOCITY){
	moveLeft = false;
	moveRight = false;
}

void Paddle::setMoveLeft(bool status){
	if(moveLeft == status) return;
	
	if(status){
		moveLeft = true;
		if(moveRight){
			xAcc = 0.0;
			xVel = 0.0;
		}
		else{
			xAcc = -PADDLE_ACCELERATION;
		}
	}
	else{
		moveLeft = false;
		if(moveRight){
			xAcc = PADDLE_ACCELERATION;
		}
		else{
			xAcc = 0.0;
			xVel = 0.0;
		}
	}
}
void Paddle::setMoveRight(bool status){
	if(moveRight == status) return;
	
	if(status){
		moveRight = true;
		if(moveLeft){
			xAcc = 0.0;
			xVel = 0.0;
		}
		else{
			xAcc = PADDLE_ACCELERATION;
		}
	}
	else{
		moveRight = false;
		if(moveLeft){
			xAcc = -PADDLE_ACCELERATION;
		}
		else{
			xAcc = 0.0;
			xVel = 0.0;
		}
	}
	
}

void Paddle::render(){
//	printf("L: %i    R: %i\n", moveLeft, moveRight);
	
	glLoadIdentity();
	glColor3f(0.9,0.1,0.1);
	glTranslatef(x, y, 0);
	
	glBegin(GL_QUADS);
		glVertex2f(0,0);
		if(isTextured()) glTexCoord2f(0.15, 0.15);
		glVertex2f(0, h);
		if(isTextured()) glTexCoord2f(0.15, 0.85);
		glVertex2f(w, h);
		if(isTextured()) glTexCoord2f(0.85,0.85);
		glVertex2f(w, 0);
		if(isTextured()) glTexCoord2f(0.85, 0.15);
	glEnd();
}



