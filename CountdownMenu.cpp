#include "CountdownMenu.h"

CountdownMenu::CountdownMenu(int time, double x, double y, double w, double h):GUIObject(0,x,y,w,h){
	font = new GraphicFont(24);
	font->init();
	count = 0;
	target = time;
	timer->start();
}

void CountdownMenu::render(){
	glColor4f(1.0, 1.0, 1.0, 1.0);
	font->positionFont(x,y);
	font->print("%i", (target-(int)count)/1000);
}
void CountdownMenu::update(){
	count = timer->getTime();
	if(count > target){
		if(callback != NULL) (*callback)();
	}
}

CountdownMenu::~CountdownMenu(){
	delete font;
}

