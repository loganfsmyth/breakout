#ifndef INCLUDED_PARTICLE_H
#define INCLUDED_PARTICLE_H

#include "DynamicObject.h"
#include "TexturedObject.h"

#define PARTICLE_BORDER	1

#define PARTICLE_RADIUS		2.0

#define PARTICLE_ACCELERATION	0.0005
#define PARTICLE_MAX_SPEED		0.4

#define PARTICLE_BOUNCE_DAMPING	0.6

class Particle: public DynamicObject, public TexturedObject{
	private:
		float fadeTime;
		double age;
		GLfloat colorArr[4];
	
	public:
		Particle(double x, double y, double xVel, double yVel, int time);
		void invertYVel();
		void render();
		void move();
		bool hasFaded();
		void setColor(GLfloat r, GLfloat g, GLfloat b);
};

#endif
