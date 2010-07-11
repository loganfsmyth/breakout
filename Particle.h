#ifndef INCLUDED_PARTICLE_H
#define INCLUDED_PARTICLE_H

#include "DynamicObject.h"
#include "TexturedObject.h"


#define PARTICLE_WIDTH		3.0
#define PARTICLE_HEIGHT	3.0

#define PARTICLE_ACCELERATION	0.01
#define PARTICLE_MAX_SPEED		0.2

#define PARTICLE_BOUNCE_DAMPING	0.9

class Particle: public DynamicObject, public TexturedObject{
	
	public:
		Particle(double x, double y, double xVel, double yVel);
		void invertYVel();
		void render();
};

#endif
