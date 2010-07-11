#include "Rect.h"

Rect::Rect(int x,int y,int w,int h){
	this->x = x;
	this->y = y;
	this->w = w;
	this->h= h;
}
bool Rect::contains(Rect* rect){
	
	int rx = rect->getX();
	int ry = rect->getY();
	int rw = rect->getW();
	int rh = rect->getH();
	
	if(containsPoint(rx, ry)) return true;
	else if(containsPoint(rx+rw, ry)) return true;
	else if(containsPoint(rx+rw, ry+rh)) return true;
	else if(containsPoint(rx, ry+rh)) return true;
	else if(rect->containsPoint(x, y)) return true;
	else if(rect->containsPoint(x+w, y)) return true;
	else if(rect->containsPoint(x, y+h)) return true;
	else if(rect->containsPoint(x+w, y+h)) return true;
	else return false;
}
bool Rect::containsPoint(int px,int py){
	if((px > x) && (px < x+w) && (py > y) && (py < y+h)){
		return true;
	}
	else return false;
}

bool Rect::nOverlap(Rect* rect){
	return (rect->containsPoint(x,y) && rect->containsPoint(x+w, y));
}
bool Rect::neOverlap(Rect* rect){
	return (rect->containsPoint(x+w, y));
}
bool Rect::eOverlap(Rect* rect){
	return (rect->containsPoint(x+w,y) && rect->containsPoint(x+w, y+h));
}
bool Rect::seOverlap(Rect* rect){
	return (rect->containsPoint(x+w, y+h));
}
bool Rect::sOverlap(Rect* rect){
	return (rect->containsPoint(x,y+h) && rect->containsPoint(x+w, y+h));
}
bool Rect::swOverlap(Rect* rect){
	return (rect->containsPoint(x,y+h));
}
bool Rect::wOverlap(Rect* rect){
	return (rect->containsPoint(x,y) && rect->containsPoint(x, y+h));
}
bool Rect::nwOverlap(Rect* rect){
	return (rect->containsPoint(x,y));
}

int Rect::getNOverlap(Rect* rect){
	return (rect->getY()+rect->getH()-y);
}
int Rect::getSOverlap(Rect* rect){
	return rect->getY()-(y+h);
}
int Rect::getEOverlap(Rect* rect){
	return rect->getX()-(x+w);
}
int Rect::getWOverlap(Rect* rect){
	return (rect->getX()+rect->getW())-x;
}


int Rect::getX(){
	return x;
}
int Rect::getY(){
	return y;
}
int Rect::getW(){
	return w;
}
int Rect::getH(){
	return h;
}
void Rect::display(){
//	printf("Rect: (%i,%i) W:%i H:%i\n", x, y, w,h);
	printf("(%i,%i)   (%i,%i)\n", x, y, x+w, y);
	printf("(%i,%i)   (%i,%i)\n", x, y+h, x+w, y+h);
	
}

int Rect::getBounceDirections(Rect* rectArr, int numRects, int direction, int* xShift, int* yShift){
	
	
	
	
	
}