#include "Level.h"


Level::Level(){
	levelData = NULL;
	blocks = NULL;
	levelSize = 0;
	levelWidth = 0;
	levelHeight = 0;
}

bool Level::open(char* filename){
	FILE* file = fopen(filename, "r");
	if(!file){
		printf("Failed to open level %s\n", filename);
		return false;
	}
	int blockCount = 0;
	
	
	char temp;
	while(!feof(file)){
		temp = fgetc(file);
		if(temp == '\n'){
			blockCount++;
			levelHeight++;
		}
		else if(temp == ' ') blockCount++;
	}
	
	levelHeight++;	//increment to account for last line of file
	
	levelWidth = (blockCount+1)/levelHeight;
	
	levelData = (int*)malloc(sizeof(int)*(blockCount+1));
	rewind(file);
	
	int charsNeeded = (blockCount+1)*2*BLOCK_NUM_SIG_FIGS;	//total length of string needed to read file
	
	char* tempSpace = (char*)malloc(sizeof(char)*charsNeeded);
	int i;
	tempSpace[0] = '\0';
	
	char* line = (char*)malloc(sizeof(char)*charsNeeded/levelHeight);
	for(i = 0; i < levelHeight;i++){
		strcpy(line, "");
		fgets(line, charsNeeded/levelHeight-1, file);
		strcat(tempSpace, line);
	}
	free(line);
	
	if(!feof(file)){
		printf("Level not Fully read\n");
		return false;
	}
	
	int last = 0, j = 0;
	for(i = 0; tempSpace[i] != '\0'; i++){
		if(tempSpace[i] == '\n' || tempSpace[i] == ' '){
			tempSpace[i] = '\0';
			sscanf(tempSpace+last, "%i", levelData+j);
			j++;
			last = i+1;
		}
	}
	sscanf(tempSpace+last, "%i", levelData+j);
	levelSize = levelWidth*levelHeight;
	free(tempSpace);
	
	
	blocks = (Block**)malloc(sizeof(Block*)*levelSize);
	
	for(i = 0; i < levelSize; i++){
		blocks[i] = NULL;
	}
	
	return true;
}
void Level::regenerateBlocks(int w, int h){

	int i;
	for(i = 0; i < levelSize; i++){
		if(blocks[i] != NULL){
			delete blocks[i];
		}
	}
	
	int blockWidth = w/levelWidth;
	int blockHeight = (h/levelHeight)*BLOCK_HEIGHT_FACTOR;
	
	int shift = (w%blockWidth)/2;	//center the blocks in the window
	
	i = 0;
	int j, type;
	for(j = 0; j < levelHeight; j++){
		for(i = 0; i < levelWidth; i++){
			type = valueAt(i,j);
			blocks[levelWidth*j+i] = new Block(type,shift +i*blockWidth, j*blockHeight, blockWidth, blockHeight);
			blocks[levelWidth*j+i]->enableTexture();
		}
	}
}
void Level::render(){
	int i,j;
	for(j = 0; j < levelHeight;j++){
		for(i = 0; i < levelWidth;i++){
			glLoadIdentity();
			blocks[j*levelWidth+i]->render();
		}
	}
}

int* Level::getLayout(int* w, int* h){
	if(w != NULL) *w = levelWidth;
	if(h != NULL) *h = levelHeight;
	
	return levelData;
}
int Level::valueAt(int x, int y){
	if(x >= levelWidth || y >= levelHeight){
		printf("Level: Attempting to Read outside Level\n");
		return -1;
	}
	
	return levelData[y*levelWidth+x];	//value of array at specified x and y positions
}

void Level::display(){
	int i;
	printf("\nWidth: %i\nHeight: %i\n", levelWidth, levelHeight);
	for(i = 0; i < levelSize; i++){
		printf("%i ", levelData[i]);
		if((i+1)%levelWidth == 0) printf("\n");
	}
}

Level::~Level(){
	if(levelData != NULL) free(levelData);	
	if(blocks != NULL){
		int i;
		for(i = 0; i < levelSize; i++){
			if(blocks[i] != NULL) delete blocks[i];
		}
		free(blocks);
	}
}

