#ifndef INCLUDED_BALL_H
#define INCLUDED_BALL_H


#include "SDL/SDL_opengl.h"

#include "Timer.h"
#include "time.h"
#include "Rect.h"
#include "DynamicObject.h"


#define BALL_BORDER	0	//border to account for transparent pixels in texture
#define BALL_RADIUS	6

#define BALL_START_VELOCITY	0.2

class Ball: public DynamicObject{
	
	private:
		bool textured;
		
	public:
		
		Ball(double x, double y);
		void render();
	
		void enableTexture();
		void disableTexture();
		
};

#endif
