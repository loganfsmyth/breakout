#include "Button.h"

Button::Button(double x, double y, double w, double h, int type, char* text):GUIObject(1,x,y,w,h){
	
	this->type = type;
	
	glowFactor = BUTTON_GLOW_CHANGE;
	
	if(type == BUTTON_TYPE_TEXT){
		if(text == NULL){
			printf("Button: No Text to print\n");
		}
		this->text = text;
		font = new GraphicFont(24);
		font->init();
	}
}
void Button::update(){
	GUIObject::update();
	
	if(isFocused()){
		int time = timer->getTime();
		if(glow >= 1.0){
			glowFactor = -BUTTON_GLOW_CHANGE;
		}
		else if(glow <=0){
			glowFactor = BUTTON_GLOW_CHANGE;
		}
		
		glow += glowFactor*time;
	}
	timer->start();
}
void Button::render(){
	GUIObject::render();
	
	glLoadIdentity();
	
	if(isTextured()) bindTexture();
	else unbindTexture();

	float multiplier = 1.0f;
	if(isFocused()){
		multiplier = glow;
	}
	
	glColor4f(1.0,1.0,1.0, 0.5+0.5*multiplier);
	
	if(type == BUTTON_TYPE_TEXT){
		font->positionFont(x,y);
		font->print(text);
//		font->print("%f", multiplier);
		
	}
	else if(type == BUTTON_TYPE_IMAGE){
		glBegin(GL_QUADS);
			glVertex2f(0,0);
			if(isTextured()) glTexCoord2f(0.0,0.0);
			glVertex2f(0, h);
			if(isTextured()) glTexCoord2f(0.0,1.0);
			glVertex2f(w, h);
			if(isTextured()) glTexCoord2f(1.0,1.0);
			glVertex2f(w, 0);
			if(isTextured()) glTexCoord2f(1.0,0.0);
		glEnd();
	}
	
}

Button::~Button(){
	if(type == BUTTON_TYPE_TEXT) delete font;
	
}

