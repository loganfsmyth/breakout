#include "GUIObject.h"


GUIObject::GUIObject(int numItems, double x, double y, double w, double h):StaticObject(x,y,w,h){
	this->maxSize = numItems;
	this->curSize = 0;
	objects = (GUIObject**)malloc(sizeof(GUIObject*)*numItems);
	
	
	callback = NULL;
	showBorder = false;
	inFocus = false;
	active = false;
	timer = new Timer();
}
void GUIObject::setFocus(bool stat){
	inFocus = stat;
}
bool GUIObject::isFocused(){
	return inFocus;
}

void GUIObject::setActive(bool stat){
	active = stat;
}
bool GUIObject::isActive(){
	return active;
}


void GUIObject::setCallback(void (*func)()){
	callback = func;
}
void GUIObject::enableBorder(){
	showBorder = true;
}
void GUIObject::render(){
	glLoadIdentity();
	
	if(showBorder){
		
		glColor4f(1.0,1.0,1.0,1.0);
		glTranslatef(x,y,0);		
		glBegin(GL_LINE_STRIP);
			glVertex2f(0,0);
			glVertex2f(0, h);
			glVertex2f(w, h);
			glVertex2f(w, 0);
			glVertex2f(0,0);
		glEnd();
	}
	
	int i;
	for(i = 0; i < curSize; i++){
		glLoadIdentity();
		objects[i]->render();
	}
}
void GUIObject::update(){
	int i;
	for(i = 0; i < curSize; i++){
		objects[i]->update();
	}
}

bool GUIObject::processMouseEvent(SDL_Event* event){
	bool contains = false;
	int i;
	for(i = 0; i < curSize; i++){
		if(objects[i]->processMouseEvent(event)) contains = true;
	}
	
	if(contains){
		setFocus(false);
		setActive(false);
		return true;
	}
	else{
		if(event->type == SDL_MOUSEMOTION){
			if(containsPoint(event->motion.x, event->motion.y)){
				setFocus(true);
				return true;
			}
			else{
				setFocus(false);
				setActive(false);
				return false;
			}
		}
		else if(event->type == SDL_MOUSEBUTTONUP){
			if(containsPoint(event->button.x, event->button.y)){
				setFocus(true);
				setActive(false);
				if(callback != NULL)  (*callback)();
				return true;
			}
			else{
				setActive(false);
				setFocus(false);
				return false;
			}
		}
		else {
			if(containsPoint(event->button.x, event->button.y)){
				setActive(true);
				setFocus(true);
				return true;
			}
			else{
				setActive(false);
				setFocus(false);
				return false;
			}
		}
	}
	
}
bool GUIObject::processKeyboardEvent(SDL_Event* event){
	
	return true;
}

void GUIObject::addObject(GUIObject* obj){
	obj->shiftX(getX());
	obj->shiftY(getY());
	
	if(curSize == maxSize) return;
	objects[curSize] = obj;
	curSize++;
}
GUIObject::~GUIObject(){
	int i;
	for(i = 0; i < curSize; i++){
		delete objects[i];
	}
	
	free(objects);
	delete timer;
}

