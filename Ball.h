#ifndef INCLUDED_BALL_H
#define INCLUDED_BALL_H


#include "SDL/SDL_opengl.h"
#include "DynamicObject.h"
#include "TexturedObject.h"


#define BALL_BORDER	1	//border to account for transparent pixels in texture
#define BALL_RADIUS	5

#define BALL_START_VELOCITY	0.25
//#define BALL_START_VELOCITY	0.05

class Ball: public DynamicObject, public TexturedObject{
	public:
		Ball(double x, double y);
		void render();
};

#endif
