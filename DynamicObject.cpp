#include "DynamicObject.h"

DynamicObject::DynamicObject(double x, double y, double w, double h, double xVel, double yVel, double xAcc, double yAcc):StaticObject(x,y,w,h){
	this->xAcc = xAcc;
	this->yAcc = yAcc;
	this->xVel = xVel;
	this->yVel = yVel;
	
	createTimer();
}
DynamicObject::DynamicObject(double x, double y, double w, double h, double xVel, double yVel):StaticObject(x,y,w,h){
	this->xAcc = 0;
	this->yAcc = 0;
	this->xVel = xVel;
	this->yVel = yVel;
	
	createTimer();
}
void DynamicObject::createTimer(){
	timer = new Timer();
	bool stat = timer->init();
	if(!stat) printf("Ball: Failed to Init TImer\n");
}
void DynamicObject::invertXVel(){
	xVel *= -1;
}
void DynamicObject::invertYVel(){
	yVel *= -1;
}

bool DynamicObject::movingNW(){
	if(xVel < 0 && yVel < 0) return true;
	else return false;
}
bool DynamicObject::movingSW(){
	if(xVel < 0 && yVel > 0) return true;
	else return false;
}
bool DynamicObject::movingNE(){
	if(xVel > 0 && yVel < 0) return true;
	else return false;
}
bool DynamicObject::movingSE(){
	if(xVel > 0 && yVel > 0) return true;
	else return false;
}
void DynamicObject::shiftX(double xShift){
	x += xShift;
}
void DynamicObject::shiftY(double yShift){
	y += yShift;
}
void DynamicObject::move(){
	
	if(!timer->isRunning()){
		timer->start();
		printf("Starting\n");
	}
	else{
		int t = timer->getTime();
		
		xVel += xAcc*t;
		yVel += yAcc*t;
		
		x += xVel*t;
		y += yVel*t;
		
		timer->start();
	}
}


int DynamicObject::checkForCollision(StaticObject* objects, int numObjects){
	if(objects == NULL) return 0;
	
	int i;
//	double x, y, w, h, 
	double bx, by, bw, bh;
	
	bx = ball->getX();
	by = ball->getY();
	bw = ball->getW();
	bh = ball->getH();
/*	
	w = blocks[0]->getW();
	h = blocks[0]->getH();
	
	
	if(w < bw || h < bh){
		printf("Level: This level was improperly designed\n       The Ball can't fit between blocks\n");
		return 0;
	}
*/
	
	int retVal = 0;
	Rect* blockRect;
	Rect* ballRect;
	int hitNE = -1;
	int hitSE = -1;
	int hitNW = -1;
	int hitSW = -1;
	
	ballRect = getRect();
	
	
	//loop through the blocks and find any blocks that intercept a corner of the ball
	//it can be assumed that a particular corner will not intersect more than 1 block
	for(i = 0; i < levelSize; i++){
		if(blocks[i]->getType() == BLOCK_HIDDEN) continue;

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



DynamicObject::~DynamicObject(){
	delete timer;
}

