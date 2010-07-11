#include "Block.h"


GLfloat Block::allColors[6][3] = {
	{0.6f, 0.2f, 0.4f},		//purple
	{0,0,1.0f},			//blue
	{0,1.0f,0},			//green
	{1.0f,1.0f,0.2f},		//yellow
	{1.0f,0.6f,0},			//orange
	{1.0f,0,0}			//red
};

Block::Block(int type, int x, int y, int w, int h){
	this->type = type;
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	
	textured = false;
}

void Block::enableTexture(){
	textured = true;
}
void Block::disableTexture(){
	textured = false;
}
void Block::render(){
	if(type == BLOCK_HIDDEN) return;
	
	glColor3fv(allColors[type]);
	
	glBegin(GL_QUADS);
		glVertex2f(x,y);
		if(textured) glTexCoord2f(0.4,0.4);
		glVertex2f(x, y+h);
		if(textured) glTexCoord2f(0.4,0.6);
		glVertex2f(x+w, y+h);
		if(textured) glTexCoord2f(0.6,0.6);
		glVertex2f(x+w, y);
		if(textured) glTexCoord2f(0.6,0.4);
	glEnd();
}

int Block::getX(){
	return x;
}
int Block::getY(){
	return y;
}
int Block::getW(){
	return w;
}
int Block::getH(){
	return h;
}
int Block::getType(){
	return type;
}
void Block::reduceCount(){
	if(type == BLOCK_HIDDEN) return;
	
	type--;
	
	if(type < 0){
		type = BLOCK_HIDDEN;
	}
}

Rect* Block::getRect(){
	return new Rect(x,y,w,h);
}
