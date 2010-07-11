#ifndef INCLUDED_BLOCK_H
#define INCLUDED_BLOCK_H

#include "SDL/SDL_opengl.h"
#include <stdio.h>

#include "StaticObject.h"
#include "TexturedObject.h"

#define BLOCK_PURPLE		0
#define BLOCK_BLUE		1
#define BLOCK_GREEN		2
#define BLOCK_YELLOW		3
#define BLOCK_ORANGE		4
#define BLOCK_RED			5
#define BLOCK_HIDDEN		99

#define BLOCK_IMAGE_BORDER	2


class Block: public StaticObject, public TexturedObject{
	private:
		int type;
		static GLfloat allColors[6][3];
	public:
		Block(int type, int x, int y, int w, int h);
		void render();
		int getType();
		bool reduceType();
};


#endif
