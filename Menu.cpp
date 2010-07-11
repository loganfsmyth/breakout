#include "Menu.h"

Menu::Menu(int numItems, double x, double y, double w, double h):GUIObject(x,y,w,h){
	this->maxSize = numItems;
	this->curSize = 0;
	objects = (GUIObject**)malloc(sizeof(GUIObject*)*numItems);
}

void Menu::addObject(GUIObject* obj){
	obj->shiftX(getX());
	obj->shiftY(getY());
	
	if(curSize == maxSize) return;
	objects[curSize] = obj;
	curSize++;
}


void Menu::render(){
	int i;
	for(i = 0; i < curSize; i++){
		glLoadIdentity();
		objects[i]->render();
	}
}
void Menu::update(){
	int i;
	for(i = 0; i < curSize; i++){
		objects[i]->update();
	}
	
}

Menu::~Menu(){
	free(objects);
}

