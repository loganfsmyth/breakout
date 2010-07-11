#ifndef INCLUDED_DYNAMICOBJECT_H
#define INCLUDED_DYNAMICOBJECT_H

#include "Rect.h"
#include "Timer.h"
#include "StaticObject.h"

class DynamicObject: public StaticObject{
	private:
		Timer* timer;
	
		double xVel;
		double yVel;
	
		double xAcc;
		double yAcc;
	
		void createTimer();
	
	public:
		DynamicObject(double x, double y, double w, double h, double xVel, double yVel, double xAcc, double yAcc);
		DynamicObject(double x, double y, double w, double h, double xVel, double yVel);
	
		bool movingNW();
		bool movingSW();
		bool movingNE();
		bool movingSE();
	
		void invertXVel();
		void invertYVel();
	
		void shiftX(double xShift);
		void shiftY(double yShift);
	
		void move();
	
		int checkForCollision(StaticObject* objects, int numObjects);
	
		virtual ~DynamicObject();
};

#endif
