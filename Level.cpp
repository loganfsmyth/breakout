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
		blocks[i] = 0;
	}
	
	return true;
}
void Level::regenerateBlocks(int w, int h){

	int i;
	for(i = 0; i < levelSize; i++){
		if(blocks[i] != NULL) delete blocks[i];
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
int Level::checkForCollision(Ball* ball, int* xShift, int* yShift){
	if(ball == NULL) return 0;
	if(blocks == NULL) return 0;
	if(levelSize == 0) return 0;
	
	
	int x, y, w, h, i, bx, by, br;
	
	bx = ball->getX();
	by = ball->getY();
	br = ball->getR();
	
	w = blocks[0]->getW();
	h = blocks[0]->getH();
	
	
	if(w < br*2 || h < br*2){
		printf("Level: This level was improperly designed\n       The Ball can't fit between blocks\n");
		return 0;
	}
	
	int retVal = 0;
	Rect* blockRect;
	Rect* ballRect;
	int hitNE = -1;
	int hitSE = -1;
	int hitNW = -1;
	int hitSW = -1;
	
	ballRect = ball->getRect();
	
	
	//loop through the blocks and find any blocks that intercept a corner of the ball
	//it can be assumed that a particular corner will not intersect more than 1 block
	for(i = 0; i < levelSize; i++){
		if(blocks[i]->getType() == BLOCK_HIDDEN) continue;
		x = blocks[i]->getX();
		y = blocks[i]->getY();
		
		blockRect = blocks[i]->getRect();

		if(ballRect->nwOverlap(blockRect)) hitNW = i;
		if(ballRect->swOverlap(blockRect)) hitSW = i;
		if(ballRect->neOverlap(blockRect)) hitNE = i;
		if(ballRect->seOverlap(blockRect)) hitSE = i;

		delete blockRect;	//the rectangles are created at each call and must be freed
		
	}
	
	
	if(hitNE != -1 && hitSW != -1){		//if hit directly at intersection of 2 blocks
		blocks[hitNE]->reduceCount();
		blocks[hitSW]->reduceCount();
	
		Rect* swBlockRect = blocks[hitSW]->getRect();
		Rect* neBlockRect = blocks[hitNE]->getRect();
		
		if(ball->movingSE()){
			*xShift = ballRect->getEOverlap(neBlockRect);
			*yShift = ballRect->getSOverlap(swBlockRect);
		}
		else if(ball->movingNW()){
			*xShift = ballRect->getWOverlap(swBlockRect);
			*yShift = ballRect->getNOverlap(neBlockRect);
		}
		else{	//hope for the best
			*xShift = 0;
			*yShift = 0;
		}
		
		delete swBlockRect;
		delete neBlockRect;

		retVal = (X_AXIS | Y_AXIS);
	}
	else if(hitNW != -1 && hitSE != -1){
		blocks[hitSE]->reduceCount();
		blocks[hitNW]->reduceCount();
		
		Rect* seBlockRect = blocks[hitSE]->getRect();
		Rect* nwBlockRect = blocks[hitNW]->getRect();
		
		if(ball->movingSW()){
			*xShift = ballRect->getWOverlap(nwBlockRect);
			*yShift = ballRect->getSOverlap(seBlockRect);
		}
		else if(ball->movingNE()){
			*xShift = ballRect->getEOverlap(seBlockRect);
			*yShift = ballRect->getNOverlap(nwBlockRect);
		}
		else{	//hope for the best
			*xShift = 0;
			*yShift = 0;
		}
		
		delete seBlockRect;
		delete nwBlockRect;
		
		retVal = (X_AXIS | Y_AXIS);
	}
	else if(hitNW != -1 && hitSW != -1){
		blocks[hitSW]->reduceCount();
		
		blockRect = blocks[hitNW]->getRect();
		if(hitSW != hitNW) blocks[hitNW]->reduceCount();
		*xShift = ballRect->getWOverlap(blockRect);
		delete blockRect;
		retVal = X_AXIS;
	}
	else if(hitNW != -1 && hitNE != -1){
		blocks[hitNW]->reduceCount();
		blockRect = blocks[hitNW]->getRect();
		if(hitNW != hitNE) blocks[hitNE]->reduceCount();
		*yShift = ballRect->getNOverlap(blockRect);
		delete blockRect;
		retVal = Y_AXIS;
	}
	else if(hitSE != -1 && hitNE != -1){
		blocks[hitSE]->reduceCount();
		blockRect = blocks[hitSE]->getRect();
		if(hitSE != hitNE) blocks[hitNE]->reduceCount();
		*xShift = ballRect->getEOverlap(blockRect);
		delete blockRect;
		retVal = X_AXIS;
	}
	else if(hitSE != -1 && hitSW != -1){
		blocks[hitSE]->reduceCount();
		blockRect = blocks[hitSE]->getRect();
		if(hitSE != hitSW) blocks[hitSW]->reduceCount();
		*yShift = ballRect->getSOverlap(blockRect);
		delete blockRect;
		retVal = Y_AXIS;
	}
	else if(hitSE != -1){
		blocks[hitSE]->reduceCount();
		blockRect = blocks[hitSE]->getRect();
		int x = ballRect->getEOverlap(blockRect);
		int y = ballRect->getSOverlap(blockRect);

		if(ball->movingSE()){
			
			if(-1*x > -1*y){	//impact on south side of ball
				retVal = Y_AXIS;
				*yShift = y;
			}
			else if(-1*x < -1*y){	//impact on East side of ball
				retVal = X_AXIS;
				*xShift = x;
			}
			else{
				retVal = X_AXIS | Y_AXIS;
				*xShift = x;
				*yShift = y;
			}
		}
		else if(ball->movingSW()){
			retVal = Y_AXIS;
			*yShift = y;
		}
		else if(ball->movingNE()){
			retVal = X_AXIS;
			*xShift = x;
		}
		else{
			printf("Level: Something wrong in SE\n");
		}
		
		delete blockRect;
	}
	else if(hitSW != -1){
		blocks[hitSW]->reduceCount();
		
		blockRect = blocks[hitSW]->getRect();

		int x = ballRect->getWOverlap(blockRect);
		int y = ballRect->getSOverlap(blockRect);
		
		if(ball->movingSW()){
			
			if(x > -1*y){	//impact on south side of ball
				retVal = Y_AXIS;
				*yShift = y;
			}
			else if(x < -1*y){		//impact on west side of ball
				retVal = X_AXIS;
				*xShift = x;
			}
			else{
				retVal = X_AXIS | Y_AXIS;
				*xShift = x;
				*yShift = y;
			}
		}
		else if(ball->movingSE()){
			retVal = Y_AXIS;
			*yShift = y;
		}
		else if(ball->movingNW()){
			retVal = X_AXIS;
			*xShift = x;
		}
		else{
			printf("Level: Something wrong in SW\n");
		}
		
		delete blockRect;

	}
	else if(hitNE != -1){
		blocks[hitNE]->reduceCount();
	
		blockRect = blocks[hitNE]->getRect();
		int x = ballRect->getEOverlap(blockRect);
		int y = ballRect->getNOverlap(blockRect);
		
		if(ball->movingNE()){
			
			if(-1*x > y){	//impact on North side of ball
				retVal = Y_AXIS;
				*yShift = y;
			}
			else if(-1*x < y){	//impact on East side of ball
				retVal = X_AXIS;
				*xShift = x;
			}
			else{
				retVal = X_AXIS | Y_AXIS;
				*xShift = x;
				*yShift = y;
			}
		}
		else if(ball->movingNW()){
			retVal = Y_AXIS;
			*yShift = y;
		}
		else if(ball->movingSE()){
			retVal = X_AXIS;
			*xShift = x;
		}
		else{
			printf("Level: Something wrong in SE\n");
		}

		delete blockRect;
		
	}
	else if(hitNW != -1){
		blocks[hitNW]->reduceCount();

		blockRect = blocks[hitNW]->getRect();
		int x = ballRect->getWOverlap(blockRect);
		int y = ballRect->getNOverlap(blockRect);
		
		if(ball->movingNW()){
			
			if(x > y){	//impact on North side of ball
				retVal = Y_AXIS;
				*yShift = y;
			}
			else if(x < y){	//impact on West side of ball
				retVal = X_AXIS;
				*xShift = x;
			}
			else{
				retVal = X_AXIS | Y_AXIS;
				*xShift = x;
				*yShift = y;
			}
		}
		else if(ball->movingNE()){
			retVal = Y_AXIS;
			*yShift = y;
		}
		else if(ball->movingSW()){
			retVal = X_AXIS;
			*xShift = x;
		}
		else{
			printf("Level: Something wrong in SE\n");
		}

		delete blockRect;

	}
	else retVal = 0;
		
	delete ballRect;
	return retVal;
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

