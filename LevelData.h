#ifndef INCLUDED_LEVEL_H
#define INCLUDED_LEVEL_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Block.h"

#define BLOCK_HEIGHT_FACTOR	3/4
#define BLOCK_NUM_SIG_FIGS	2


class LevelData{
	public:
		LevelData();
		
		bool open(char* filename);
		void regenerateBlocks(int w, int h);
		int valueAt(int x, int y);
		void display();
		void render();
		Block** getBlocks(int* size = NULL);
		void setBlockImpact(int* blocksHit, int numHit);
		int getNumVisible();
		void setTexture(GLuint tex, double x, double y, double w, double h);
		
		~LevelData();
	private:
		Block** blocks;
		int* levelData;
		int levelSize;
		int levelWidth;
		int levelHeight;
		int numVisible;
		
};

#endif
