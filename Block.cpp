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

void Block::render(){
	if(type == BLOCK_HIDDEN) return;
	
	glLoadIdentity();
	glColor3fv(allColors[type]);
	glTranslatef(x,y, 0);
	
	glBegin(GL_QUADS);
		glVertex2f(0,0);
		if(isTextured()) glTexCoord2f(0.4,0.4);
		glVertex2f(0, h);
		if(isTextured()) glTexCoord2f(0.4,0.6);
		glVertex2f(w, h);
		if(isTextured()) glTexCoord2f(0.6,0.6);
		glVertex2f(w, 0);
		if(isTextured()) glTexCoord2f(0.6,0.4);
	glEnd();
}
int Block::getType(){
	return type;
}
bool Block::reduceType(){
	if(type == BLOCK_HIDDEN){
		printf("BlocK: Reduce::This shouldn't happen\n");
		return false;
	}
	type--;
	
	if(type < 0){
		type = BLOCK_HIDDEN;
		return true;
	}
	else return false;
}
