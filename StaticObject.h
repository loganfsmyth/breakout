#ifndef INCLUDED_STATICOBJECT_H
#define INCLUDED_STATICOBJECT_H

#include <stdio.h>
#include "Rect.h"

class StaticObject{
	
	protected:
		double x,y,w,h;
	public:
		StaticObject(double x, double y, double w, double h);
		double getX();
		double getY();
		double getW();
		double getH();
//		Rect* getRect();
	
	
		bool contains(StaticObject* rect);
		bool containsPoint(double px,double py);
	
		bool nOverlap(StaticObject* rect);
		bool neOverlap(StaticObject* rect);
		bool eOverlap(StaticObject* rect);
		bool seOverlap(StaticObject* rect);
		bool sOverlap(StaticObject* rect);
		bool swOverlap(StaticObject* rect);
		bool wOverlap(StaticObject* rect);
		bool nwOverlap(StaticObject* rect);
	
		double getNOverlap(StaticObject* rect);
		double getSOverlap(StaticObject* rect);
		double getEOverlap(StaticObject* rect);
		double getWOverlap(StaticObject* rect);
	
		virtual void render() = 0;
		virtual ~StaticObject();
};

#endif
