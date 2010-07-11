#ifndef INCLUDED_COLLISION_H
#define INCLUDED_COLLISION_H

#include "Particle.h"
#include "StaticObject.h"

#include <math.h>
#include <time.h>
#define PI	3.1415926535

#define COLLISION_NUM_PARTICLES		40

#define COLLISION_PARTICLE_VELOCITY	0.30

#define COLLISION_FADE_TIME			1200

class Collision{
	private:
		Particle** particles;
	public:
		Collision(double x, double y);
		void render();
		void move();
		bool hasFaded();
		void setTexture(GLuint tex);
		void processCollisions(StaticObject** objects, int numObjects);
		void setColor(GLfloat r, GLfloat g, GLfloat b);
	
		virtual ~Collision();
};

#endif
