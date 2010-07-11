#include "Collision.h"


Collision::Collision(double x, double y){
	particles = (Particle**)malloc(sizeof(Particle*)*COLLISION_NUM_PARTICLES);
	
	srand(time(NULL));
	
	double xVel, yVel;
	int i;
	
	for(i = 0; i < COLLISION_NUM_PARTICLES; i++){
		xVel = COLLISION_PARTICLE_VELOCITY*cos(2*PI*i/COLLISION_NUM_PARTICLES) * (((rand()%10)/20.0)+0.5);
		yVel = COLLISION_PARTICLE_VELOCITY*sin(2*PI*i/COLLISION_NUM_PARTICLES) * (((rand()%10)/20.0)+0.5);
		
		particles[i] = new Particle(x,y,xVel, yVel, COLLISION_FADE_TIME);
	}
	
}
void Collision::setColor(GLfloat r, GLfloat g, GLfloat b){
	int i;
	for(i = 0; i < COLLISION_NUM_PARTICLES; i++) particles[i]->setColor(r,g,b);
	
}
void Collision::processCollisions(StaticObject** objects, int numObjects){
	int i, collision;
	double xShift, yShift;
	for(i = 0; i < COLLISION_NUM_PARTICLES; i++){
		xShift = 0;
		yShift = 0;
		collision = particles[i]->checkForCollision(objects, numObjects, &xShift, &yShift);
	
		if((collision & X_AXIS) == X_AXIS) particles[i]->invertXVel();
		if((collision & Y_AXIS) == Y_AXIS) particles[i]->invertYVel();

		particles[i]->shiftX(xShift);
		particles[i]->shiftY(yShift);
	}
}
void Collision::setTexture(GLuint tex){
	int i;
	for(i = 0; i < COLLISION_NUM_PARTICLES; i++) particles[i]->setTexture(tex, 0.0, 0.0, 1.0, 1.0);
	
}
void Collision::render(){
	int i;
	for(i = 0; i < COLLISION_NUM_PARTICLES; i++) particles[i]->render();
}
void Collision::move(){
	int i;
	for(i = 0; i < COLLISION_NUM_PARTICLES; i++) particles[i]->move();
}
bool Collision::hasFaded(){
	bool faded = true;
	int i;
	for(i = 0; i < COLLISION_NUM_PARTICLES; i++){
		if(!particles[i]->hasFaded()) faded = false;
	}
	return faded;
}
Collision::~Collision(){
	int i;
	for(i = 0; i < COLLISION_NUM_PARTICLES; i++) delete particles[i];
	
	free(particles);
}

