#ifndef INCLUDED_LEVEL_H
#define INCLUDED_LEVEL_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Block.h"
#include "Ball.h"

#define BLOCK_HEIGHT_FACTOR	3/4
#define BLOCK_NUM_SIG_FIGS	2

#define X_AXIS	1
#define Y_AXIS	2


class Level{
	public:
		Level();
		
		bool open(char* filename);
		int* getLayout(int* w, int* h);
		void regenerateBlocks(int w, int h);
		int valueAt(int x, int y);
		void display();
		void render();
		int checkForCollision(Ball* ball, int* xShift, int* yShift);
		
		void setBlockTexture(GLuint tex);
		void setParticleTexture(GLuint tex);
		
		~Level();
	private:
		Block** blocks;
		int* levelData;
		int levelSize;
		int levelWidth;
		int levelHeight;
	
		
};

#endif
