#include "StaticObject.h"

StaticObject::StaticObject(double x, double y, double w, double h){
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

double StaticObject::getX(){
	return x;
}
double StaticObject::getY(){
	return y;
}
double StaticObject::getW(){
	return w;
}
double StaticObject::getH(){
	return h;
}


void StaticObject::shiftX(double xShift){
	x += xShift;
}
void StaticObject::shiftY(double yShift){
	y += yShift;
}
/*
Rect* StaticObject::getRect(){
	return new Rect(x,y,w,h);
}
*/

bool StaticObject::contains(StaticObject* obj){
	
	double rx = obj->getX();
	double ry = obj->getY();
	double rw = obj->getW();
	double rh = obj->getH();
	
	if(containsPoint(rx, ry)) return true;
	else if(containsPoint(rx+rw, ry)) return true;
	else if(containsPoint(rx+rw, ry+rh)) return true;
	else if(containsPoint(rx, ry+rh)) return true;
	else if(obj->containsPoint(x, y)) return true;
	else if(obj->containsPoint(x+w, y)) return true;
	else if(obj->containsPoint(x, y+h)) return true;
	else if(obj->containsPoint(x+w, y+h)) return true;
	else return false;
}
bool StaticObject::containsPoint(double px,double py){
	if((px > x) && (px < x+w) && (py > y) && (py < y+h)){
		return true;
	}
	else return false;
}

bool StaticObject::nOverlap(StaticObject* obj){
	return (obj->containsPoint(x,y) && obj->containsPoint(x+w, y));
}
bool StaticObject::neOverlap(StaticObject* obj){
	return (obj->containsPoint(x+w, y));
}
bool StaticObject::eOverlap(StaticObject* obj){
	return (obj->containsPoint(x+w,y) && obj->containsPoint(x+w, y+h));
}
bool StaticObject::seOverlap(StaticObject* obj){
	return (obj->containsPoint(x+w, y+h));
}
bool StaticObject::sOverlap(StaticObject* obj){
	return (obj->containsPoint(x,y+h) && obj->containsPoint(x+w, y+h));
}
bool StaticObject::swOverlap(StaticObject* obj){
	return (obj->containsPoint(x,y+h));
}
bool StaticObject::wOverlap(StaticObject* obj){
	return (obj->containsPoint(x,y) && obj->containsPoint(x, y+h));
}
bool StaticObject::nwOverlap(StaticObject* obj){
	return (obj->containsPoint(x,y));
}

double StaticObject::getNOverlap(StaticObject* obj){
	return (obj->getY()+obj->getH()-y);
}
double StaticObject::getSOverlap(StaticObject* obj){
	return obj->getY()-(y+h);
}
double StaticObject::getEOverlap(StaticObject* obj){
	return obj->getX()-(x+w);
}
double StaticObject::getWOverlap(StaticObject* obj){
	return (obj->getX()+obj->getW())-x;
}

StaticObject::~StaticObject(){
	
}
