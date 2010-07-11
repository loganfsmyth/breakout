#include "DynamicObject.h"

DynamicObject::DynamicObject(double x, double y, double w, double h, double xVel, double yVel, double xAcc, double yAcc, double xVelMax, double yVelMax):StaticObject(x,y,w,h){
	this->xAcc = xAcc;
	this->yAcc = yAcc;
	this->xVel = xVel;
	this->yVel = yVel;
	this->xVelMax = xVelMax;
	this->yVelMax = yVelMax;
	
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
void DynamicObject::pause(){
	timer->stop();
}
void DynamicObject::unpause(){
	timer->start();
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
void DynamicObject::move(){
	
//	printf("XVel:%f  YVel:%f   XAcc:%f  YAcc:%f\n", xVel, yVel, xAcc, yAcc);
	
	if(!timer->isRunning()){
		timer->start();
	}
	else{
		int t = timer->getTime();
		
		xVel += xAcc*t;
		yVel += yAcc*t;
		
		if(xVelMax != VELOCITY_UNLIMITED){
			if(xVel > xVelMax) xVel = xVelMax;
			else if(xVel < -1*xVelMax) xVel = -1*xVelMax;
		}
		if(yVelMax != VELOCITY_UNLIMITED){
			if(yVel > yVelMax) yVel = yVelMax;
			else if(yVel < -1*yVelMax) yVel = -1*yVelMax;
		}
		
		x += xVel*t;
		y += yVel*t;
		
		timer->start();
	}
}

double DynamicObject::abs(double i){
	if(i < 0) return -1*i;
	else return i;
}

int DynamicObject::checkForCollision(StaticObject** objects, int numObjects,double* xShift, double* yShift, int* objCollidedWith, int* numCollided){
	if(objects == NULL || numObjects == 0) return 0;
	
	int i;	
	int retVal = 0;
	int hitNE = -1;
	int hitSE = -1;
	int hitNW = -1;
	int hitSW = -1;
	
	//loop through the blocks and find any blocks that intercept a corner of the ball
	//it can be assumed that a particular corner will not intersect more than 1 block
	for(i = 0; i < numObjects; i++){
		if(objects[i] == this) continue;
		if(nwOverlap(objects[i])) hitNW = i;
		if(swOverlap(objects[i])) hitSW = i;
		if(neOverlap(objects[i])) hitNE = i;
		if(seOverlap(objects[i])) hitSE = i;
	}
	
	
	if(hitNE != -1 && hitSW != -1){		//if hit directly at intersection of 2 blocks
		
		if(movingSE()){
			if(xShift != NULL) *xShift = getEOverlap(objects[hitNE]);
			if(yShift != NULL) *yShift = getSOverlap(objects[hitSW]);
		}
		else if(movingNW()){
			if(xShift != NULL) *xShift = getWOverlap(objects[hitSW]);
			if(yShift != NULL) *yShift = getNOverlap(objects[hitNE]);
		}
		else{	//hope for the best
			if(xShift != NULL) *xShift = 0;
			if(yShift != NULL) *yShift = 0;
		}
		retVal = (X_AXIS | Y_AXIS);
	}
	else if(hitNW != -1 && hitSE != -1){
		if(movingSW()){
			if(xShift != NULL) *xShift = getWOverlap(objects[hitNW]);
			if(yShift != NULL) *yShift = getSOverlap(objects[hitSE]);
		}
		else if(movingNE()){
			if(xShift != NULL) *xShift = getEOverlap(objects[hitSE]);
			if(yShift != NULL) *yShift = getNOverlap(objects[hitNW]);
		}
		else{	//hope for the best
			if(xShift != NULL) *xShift = 0;
			if(yShift != NULL) *yShift = 0;
		}
		
		retVal = (X_AXIS | Y_AXIS);
	}
	else if(hitNW != -1 && hitSW != -1){
		if(xShift != NULL) *xShift = getWOverlap(objects[hitNW]);
		retVal = X_AXIS;
	}
	else if(hitNW != -1 && hitNE != -1){
		if(yShift != NULL) *yShift = getNOverlap(objects[hitNW]);
		retVal = Y_AXIS;
	}
	else if(hitSE != -1 && hitNE != -1){
		if(xShift != NULL) *xShift = getEOverlap(objects[hitNE]);
		retVal = X_AXIS;
	}
	else if(hitSE != -1 && hitSW != -1){
		if(yShift != NULL) *yShift = getSOverlap(objects[hitSE]);
		retVal = Y_AXIS;
	}
	else if(hitSE != -1){
		double x = getEOverlap(objects[hitSE]);
		double y = getSOverlap(objects[hitSE]);

		if(movingSE()){
			
			if(-1*x > -1*y){	//impact on south side of ball
				retVal = Y_AXIS;
				if(yShift != NULL) *yShift = y;
			}
			else if(-1*x < -1*y){	//impact on East side of ball
				retVal = X_AXIS;
				if(xShift != NULL) *xShift = x;
			}
			else{
				retVal = X_AXIS | Y_AXIS;
				if(xShift != NULL) *xShift = x;
				if(yShift != NULL) *yShift = y;
			}
		}
		else if(movingSW()){
			retVal = Y_AXIS;
			if(yShift != NULL) *yShift = y;
		}
		else if(movingNE()){
			retVal = X_AXIS;
			if(xShift != NULL) *xShift = x;
		}
		else{
			printf("Level: Something wrong in SE\n");
		}
	}
	else if(hitSW != -1){
		
		double x = getWOverlap(objects[hitSW]);
		double y = getSOverlap(objects[hitSW]);
		
		if(movingSW()){
			
			if(x > -1*y){	//impact on south side of ball
				retVal = Y_AXIS;
				if(yShift != NULL) *yShift = y;
			}
			else if(x < -1*y){		//impact on west side of ball
				retVal = X_AXIS;
				if(xShift != NULL) *xShift = x;
			}
			else{
				retVal = X_AXIS | Y_AXIS;
				if(xShift != NULL) *xShift = x;
				if(yShift != NULL) *yShift = y;
			}
		}
		else if(movingSE()){
			retVal = Y_AXIS;
			if(yShift != NULL) *yShift = y;
		}
		else if(movingNW()){
			retVal = X_AXIS;
			if(xShift != NULL) *xShift = x;
		}
		else{
			printf("Level: Something wrong in SW\n");
		}
	}
	else if(hitNE != -1){
		double x = getEOverlap(objects[hitNE]);
		double y = getNOverlap(objects[hitNE]);
		
		if(movingNE()){
			
			if(-1*x > y){	//impact on North side of ball
				retVal = Y_AXIS;
				if(yShift != NULL) *yShift = y;
			}
			else if(-1*x < y){	//impact on East side of ball
				retVal = X_AXIS;
				if(xShift != NULL) *xShift = x;
			}
			else{
				retVal = X_AXIS | Y_AXIS;
				if(xShift != NULL) *xShift = x;
				if(yShift != NULL) *yShift = y;
			}
		}
		else if(movingNW()){
			retVal = Y_AXIS;
			if(yShift != NULL) *yShift = y;
		}
		else if(movingSE()){
			retVal = X_AXIS;
			if(xShift != NULL) *xShift = x;
		}
		else{
			printf("Level: Something wrong in SE\n");
		}
		
	}
	else if(hitNW != -1){
		double x = getWOverlap(objects[hitNW]);
		double y = getNOverlap(objects[hitNW]);
		
		if(movingNW()){
			
			if(x > y){	//impact on North side of ball
				retVal = Y_AXIS;
				if(yShift != NULL) *yShift = y;
			}
			else if(x < y){	//impact on West side of ball
				retVal = X_AXIS;
				if(xShift != NULL) *xShift = x;
			}
			else{
				retVal = X_AXIS | Y_AXIS;
				if(xShift != NULL) *xShift = x;
				if(yShift != NULL) *yShift = y;
			}
		}
		else if(movingNE()){
			retVal = Y_AXIS;
			if(yShift != NULL) *yShift = y;
		}
		else if(movingSW()){
			retVal = X_AXIS;
			if(xShift != NULL) *xShift = x;
		}
		else{
			printf("Level: Something wrong in SE\n");
		}
	}
	else retVal = 0;
	
	if(objCollidedWith != NULL){
		i = 0;
		
		if(hitNE != -1){
			objCollidedWith[i] = hitNE;
			i++;
		}
		if(hitSE != -1){
			objCollidedWith[i] = hitSE;
			i++;
		}
		if(hitNW != -1){
			objCollidedWith[i] = hitNW;
			i++;
		}
		if(hitSW != -1){
			objCollidedWith[i] = hitSW;
			i++;
		}
		
		if(numCollided != NULL) *numCollided = i;
	}
	return retVal;
}



DynamicObject::~DynamicObject(){
	delete timer;
}

