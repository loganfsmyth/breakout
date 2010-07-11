#include "LevelData.h"


LevelData::LevelData(){
	levelData = NULL;
	blocks = NULL;
	levelSize = 0;
	levelWidth = 0;
	levelHeight = 0;
}

bool LevelData::open(char* filename){
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
void LevelData::regenerateBlocks(int w, int h){

	int i;
	for(i = 0; i < levelSize; i++){
		if(blocks[i] != NULL){
			delete blocks[i];
		}
	}
	
	int blockWidth = w/levelWidth;
	int blockHeight = (h/levelHeight)*BLOCK_HEIGHT_FACTOR;
	
	int shift = (w%blockWidth)/2;	//center the blocks in the window
	
	int countFront = 0;
	int countEnd = levelSize;
	
	i = 0;
	int j, type;
	for(j = 0; j < levelHeight; j++){
		for(i = 0; i < levelWidth; i++){
			type = valueAt(i,j);
			
			//sort hidden blocks onto the front of the stack
			if(type == BLOCK_HIDDEN){
				countEnd--;
				blocks[countEnd] = new Block(type,shift +i*blockWidth, j*blockHeight, blockWidth, blockHeight);
			}
			else{
				blocks[countFront] = new Block(type,shift +i*blockWidth, j*blockHeight, blockWidth, blockHeight);
				countFront++;
			}
		}
	}
	
	numVisible =  countFront;
	
}
void LevelData::setTexture(GLuint tex, double x, double y, double w, double h){
	int i;
	for(i = 0; i < levelSize; i++){
		blocks[i]->setTexture(tex, x, y,w, h);
	}
}

int LevelData::getNumVisible(){
	return numVisible;
}
void LevelData::render(){
	int i,j;
	for(j = 0; j < levelHeight;j++){
		for(i = 0; i < levelWidth;i++){
			glLoadIdentity();
			blocks[j*levelWidth+i]->render();
		}
	}
}
void LevelData::setBlockImpact(int* blocksHit, int numHit){
	bool found = false;
	int i, j;
	for(i = 0; i < numHit; i++){
		found = false;
		for(j =i+1; j < numHit; j++){
			if(blocksHit[i] == blocksHit[j]){
				found = true;
			}
		}
		
		if(!found){
			bool nowHidden = blocks[blocksHit[i]]->reduceType();
			if(nowHidden){
				numVisible--;
				Block* temp = blocks[blocksHit[i]];
				blocks[blocksHit[i]] = blocks[numVisible];
				blocks[numVisible] = temp;
			}
		}
	}
	
}
int LevelData::valueAt(int x, int y){
	if(x >= levelWidth || y >= levelHeight){
		printf("Level: Attempting to Read outside Level\n");
		return -1;
	}
	
	return levelData[y*levelWidth+x];	//value of array at specified x and y positions
}


Block** LevelData::getBlocks(int* size){
//	if(size != NULL) *size = levelSize;
	if(size != NULL) *size = numVisible;

	return blocks;
	
}

void LevelData::display(){
	int i;
	printf("\nWidth: %i\nHeight: %i\n", levelWidth, levelHeight);
	for(i = 0; i < levelSize; i++){
		printf("%i ", levelData[i]);
		if((i+1)%levelWidth == 0) printf("\n");
	}
}

LevelData::~LevelData(){
	if(levelData != NULL) free(levelData);	
	if(blocks != NULL){
		int i;
		for(i = 0; i < levelSize; i++){
			if(blocks[i] != NULL) delete blocks[i];
		}
		free(blocks);
	}
}

