#ifndef INCLUDED_DYNAMICOBJECT_H
#define INCLUDED_DYNAMICOBJECT_H

#include "Timer.h"
#include "StaticObject.h"


#define X_AXIS	1
#define Y_AXIS	2

#define VELOCITY_UNLIMITED 0.0


class DynamicObject: public StaticObject{
	protected:
		Timer* timer;
	
		double xVel;
		double yVel;
	
		double xVelMax;
		double yVelMax;
	
		double xAcc;
		double yAcc;
	
		double abs(double i);
	
	public:
		DynamicObject(double x, double y, double w, double h, double xVel = 0.0, double yVel = 0.0, double xAcc = 0.0, double yAcc = 0.0, double xVelMax = VELOCITY_UNLIMITED, double yVelMax = VELOCITY_UNLIMITED);
	
		bool movingNW();
		bool movingSW();
		bool movingNE();
		bool movingSE();
	
		void invertXVel();
		void invertYVel();
	
		void pause();
		void unpause();
		
		void move();
	
		int checkForCollision(StaticObject** objects, int numObjects,double* xShift = NULL, double* yShift = NULL, int* objCollidedWith = NULL, int* numCollided = NULL);
	
		virtual ~DynamicObject();
};

#endif
