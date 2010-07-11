#ifndef INCLUDED_BALL_H
#define INCLUDED_BALL_H


#include "SDL/SDL_opengl.h"

#include "Timer.h"
#include "time.h"
#include "Rect.h"

#define BALL_BORDER	0	//border to account for transparent pixels in texture
#define BALL_RADIUS	6

class Ball{
	
	private:
		int x;
		int y;
	
		float xVel;
		float yVel;
		Timer* timer;
		bool textured;
		
	public:
		
		Ball(int x, int y);
		void move();
		void render();
		void invertXVel();
		void invertYVel();
	
		int getX();
		int getY();
		int getR();
		void setX(int x);
		void setY(int y);
		Rect* getRect();
		
		void enableTexture();
		void disableTexture();
	
		bool movingNW();
		bool movingSW();
		bool movingNE();
		bool movingSE();
		
		~Ball();
		
};

#endif
