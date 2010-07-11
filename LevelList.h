#ifndef INCLUDED_LEVELLIST_H
#define INCLUDED_LEVELLIST_H

#include <stdio.h>
#include "LevelData.h"
#include "string.h"

#define LEVEL_DIRECTORY	"Levels/"
#define LEVEL_LIST_FILE		"Levels.lvl"

class LevelList{
	private:
		char** levels;
		int numLevels;
		int curLevel;
		bool started;
	public:
		LevelList();
		bool init();
		LevelData* getNext();
		int getNumLevels();
		~LevelList();
};

#endif
