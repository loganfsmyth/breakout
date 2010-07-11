#ifndef INCLUDED_BLOCK_H
#define INCLUDED_BLOCK_H

#include "SDL/SDL_opengl.h"
#include <stdio.h>

#include "Rect.h"
#include "StaticObject.h"

#define BLOCK_PURPLE		0
#define BLOCK_BLUE		1
#define BLOCK_GREEN		2
#define BLOCK_YELLOW		3
#define BLOCK_ORANGE		4
#define BLOCK_RED			5
#define BLOCK_HIDDEN		99

#define BLOCK_IMAGE_BORDER	2


class Block: public StaticObject{
	private:
		int type;
		static GLfloat allColors[6][3];
		bool textured;
	public:
		Block(int type, int x, int y, int w, int h);// : StaticObject(x,y,w,h);
		void update();
		void render();
		int getType();
	
		void enableTexture();
		void disableTexture();
	
		void reduceCount();
};


#endif
