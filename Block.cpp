#include "Block.h"


GLfloat Block::allColors[6][3] = {
	{0.6f, 0.2f, 0.4f},		//purple
	{0,0,1.0f},			//blue
	{0,1.0f,0},			//green
	{1.0f,1.0f,0.2f},		//yellow
	{1.0f,0.6f,0},			//orange
	{1.0f,0,0}			//red
};

Block::Block(int type, int x, int y, int w, int h):StaticObject(x,y,w,h){
	this->type = type;
}

void Block::getColor(GLfloat* r, GLfloat* g, GLfloat* b){
	if(type == BLOCK_HIDDEN) return;
	*r = allColors[type][0];
	*g = allColors[type][1];
	*b = allColors[type][2];
	
}

bool Block::hasFaded(){
	return true;
	
	if(type != BLOCK_HIDDEN) return false;
	
	bool faded = true;
	int i;
	for(i = 0; i < BLOCK_DISSOLVE_PARTICLES; i++){
		if(!particles[i]->hasFaded()) faded = false;
	}
	return faded;
}
void Block::render(){
	if(type == BLOCK_HIDDEN){
		if(hasFaded()) return;
		
		int i;
		for(i = 0; i < BLOCK_DISSOLVE_PARTICLES; i++){
			particles[i]->render();
		}
	}
	else{	
		bindTexture();
		
		glLoadIdentity();
		glColor3fv(allColors[type]);
		glTranslatef(x-BLOCK_IMAGE_BORDER,y-BLOCK_IMAGE_BORDER, 0);
		
		glBegin(GL_QUADS);
			if(isTextured()) glTexCoord2f(0.0,0.0);
			glVertex2f(0,0);
			if(isTextured()) glTexCoord2f(0.0,1.0);
			glVertex2f(0, h+BLOCK_IMAGE_BORDER*2);
			if(isTextured()) glTexCoord2f(1.0,1.0);
			glVertex2f(w+BLOCK_IMAGE_BORDER*2, h+BLOCK_IMAGE_BORDER*2);
			if(isTextured()) glTexCoord2f(1.0,0.0);
			glVertex2f(w+BLOCK_IMAGE_BORDER*2, 0);
		glEnd();
			
		unbindTexture();
	}
}
int Block::getType(){
	return type;
}
bool Block::reduceType(){
	if(type == BLOCK_HIDDEN){
		printf("Block: Reduce::This shouldn't happen\n");
		return false;
	}
	type--;
	
	if(type < 0){
		type = BLOCK_HIDDEN;
		return true;
	}
	else return false;
}
