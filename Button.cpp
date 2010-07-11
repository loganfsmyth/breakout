#include "Button.h"

char* text;
GraphicFont* font;
float glow;
bool inFocus;


Button::Button(double x, double y, double w, double h, int type, char* text):GUIObject(x,y,w,h){
	timer = new Timer();
	timer->start();
	this->type = type;
	
	glowFactor = BUTTON_GLOW_CHANGE;
	
	if(type == BUTTON_TYPE_TEXT){
		if(text == NULL){
			printf("Button: No Text to print\n");
		}
		this->text = text;
		font = new GraphicFont();
		font->init();
	}
	
	setFocus(true);
	
}
void Button::update(){
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
	
	if(isTextured()) bindTexture();
	else unbindTexture();

	glColor3f(1.0,1.0,1.0);
	
	if(type == BUTTON_TYPE_TEXT){
		font->positionFont(x,y);
		font->print(text);
//		font->print("%f", glow);
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
	glTranslatef(x,y,0);		
	glBegin(GL_LINE_STRIP);
		glVertex2f(0,0);
		glVertex2f(0, h);
		glVertex2f(w, h);
		glVertex2f(w, 0);
		glVertex2f(0,0);
	glEnd();
	

	if(isFocused()){
		glColor4f(0.0, 0.0, 0.0, 0.5*glow);
	
		glBegin(GL_QUADS);
			glVertex2f(0, 0);
			glVertex2f(0, h);
			glVertex2f(w, h);
			glVertex2f(w, 0);
		glEnd();
	}

}

Button::~Button(){
	
	delete timer;
}

