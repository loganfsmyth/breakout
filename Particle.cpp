#include "Particle.h"

Particle::Particle(double x, double y, double xVel, double yVel):DynamicObject(x,y,PARTICLE_WIDTH, PARTICLE_HEIGHT, xVel, yVel, 0.0, PARTICLE_ACCELERATION, 0.0, PARTICLE_MAX_SPEED){
	
	
}

//gravity!
void Particle::invertYVel(){
	yVel = -1*PARTICLE_BOUNCE_DAMPING*yVel;
}
void Particle::render(){
	
	
	
}
