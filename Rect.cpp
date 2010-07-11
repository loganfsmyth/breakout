#include "Rect.h"

Rect::Rect(double x,double y,double w,double h){
	this->x = x;
	this->y = y;
	this->w = w;
	this->h= h;
}
bool Rect::contains(Rect* rect){
	
	double rx = rect->getX();
	double ry = rect->getY();
	double rw = rect->getW();
	double rh = rect->getH();
	
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
bool Rect::containsPoint(double px,double py){
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

double Rect::getNOverlap(Rect* rect){
	return (rect->getY()+rect->getH()-y);
}
double Rect::getSOverlap(Rect* rect){
	return rect->getY()-(y+h);
}
double Rect::getEOverlap(Rect* rect){
	return rect->getX()-(x+w);
}
double Rect::getWOverlap(Rect* rect){
	return (rect->getX()+rect->getW())-x;
}


double Rect::getX(){
	return x;
}
double Rect::getY(){
	return y;
}
double Rect::getW(){
	return w;
}
double Rect::getH(){
	return h;
}
void Rect::display(){
//	printf("Rect: (%i,%i) W:%i H:%i\n", x, y, w,h);
	printf("(%f,%f)   (%f,%f)\n", x, y, x+w, y);
	printf("(%f,%f)   (%f,%f)\n", x, y+h, x+w, y+h);
	
}

