#ifndef INCLUDED_PADDLE_H
#define INCLUDED_PADDLE_H

#include "SDL/SDL_opengl.h"
#include "DynamicObject.h"
#include "TexturedObject.h"

#define PADDLE_MAX_VELOCITY	0.35
#define PADDLE_ACCELERATION	0.0008

#define PADDLE_HEIGHT			10.0

class Paddle: public DynamicObject, public TexturedObject{
	protected:
		bool moveLeft, moveRight;
	public:
		Paddle(double x, double y, double w);
		void setMoveLeft(bool status);
		void setMoveRight(bool status);
		void render();
		void move();
		bool movingLeft();
		bool movingRight();
};

#endif
