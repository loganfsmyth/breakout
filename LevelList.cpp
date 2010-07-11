#include "LevelList.h"

LevelList::LevelList(){
	started = false;
}
bool LevelList::init(){
	char* dir = LEVEL_DIRECTORY;
	char* shortFilename = LEVEL_LIST_FILE;
	char* filename = (char*)malloc(sizeof(char*)*(strlen(dir)+strlen(shortFilename)+1));
	strcpy(filename, dir);
	strcat(filename, shortFilename);
	
	FILE* file = fopen(filename, "r");
	
	if(!file) return false;
		
	int count = 0;
	char found;
	while(!feof(file)){
		found = fgetc(file);
		if(found == '\n' || found == '\0') count++;
	}
	rewind(file);
	numLevels = count+1;
	curLevel = 0;
	char* tempSpace = (char*)malloc(sizeof(char)*100);
	levels = (char**)malloc(sizeof(char*)*numLevels);
	
	int i;
	for(i = 0;i < numLevels; i++){
		fgets(tempSpace, 99, file);
		levels[i] = (char*)malloc(sizeof(char)*(strlen(dir)+strlen(tempSpace)+1));
		strcpy(levels[i], dir);
		strcat(levels[i], tempSpace);
		if(levels[i][strlen(levels[i])-1] == '\n') levels[i][strlen(levels[i])-1] = '\0';	//strip off \n
	}
	free(tempSpace);
	fclose(file);
	started = true;
	return true;
}
LevelData* LevelList::getLevel(){
	LevelData* lev = new LevelData();
	lev->open(levels[curLevel]);
	
	return lev;
}
void LevelList::restartLevels(){
	curLevel = 0;
}
void LevelList::nextLevel(){
	curLevel++;
	
	if(curLevel == numLevels) curLevel = numLevels-1;
}
int LevelList::getNumLevels(){
	return numLevels;
}
LevelList::~LevelList(){
	if(!started) return;
	int i;
	for(i = 0; i < numLevels; i++){
		free(levels[i]);
	}
	free(levels);
	
}

