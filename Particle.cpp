#include "Particle.h"

Particle::Particle(double x, double y, double xVel, double yVel, int fadeTime):DynamicObject(x,y,PARTICLE_RADIUS*2, PARTICLE_RADIUS*2, xVel, yVel, 0.0, PARTICLE_ACCELERATION, 0.0, PARTICLE_MAX_SPEED){
	this->fadeTime = (float)fadeTime;
	this->age = 0.0;
	
	colorArr[0] = 1.0;
	colorArr[1] = 1.0;
	colorArr[2] = 1.0;
}
bool Particle::hasFaded(){
	if(age > fadeTime){
		return true;
	}
	else return false;
}
void Particle::move(){
	age += timer->getTime();	// increment age because timer restarted every move
	
	DynamicObject::move();
}
void Particle::setColor(GLfloat r, GLfloat g, GLfloat b){
	colorArr[0] = r;
	colorArr[1] = g;
	colorArr[2] = b;
}

//inelastic collision
void Particle::invertYVel(){
	yVel = -1*PARTICLE_BOUNCE_DAMPING*yVel;
}
void Particle::render(){
	
	if(hasFaded()) return;
	
	colorArr[3] = 1-age/fadeTime;
	
	bindTexture();
	
	glLoadIdentity();
	
	glColor4fv(colorArr);
	glTranslatef(x-PARTICLE_BORDER, y-PARTICLE_BORDER, 0);
	
	glBegin(GL_QUADS);
		if(isTextured()) glTexCoord2f(0.0, 0.0);
		glVertex2f(0,0);
		if(isTextured()) glTexCoord2f(0.0, 1.0);
		glVertex2f(0, w+PARTICLE_BORDER*2);
		if(isTextured()) glTexCoord2f(1.0,1.0);
		glVertex2f(h+PARTICLE_BORDER*2, w+PARTICLE_BORDER*2);
		if(isTextured()) glTexCoord2f(1.0, 0.0);
		glVertex2f(h+PARTICLE_BORDER*2, 0);
	glEnd();
		
	unbindTexture();
}
