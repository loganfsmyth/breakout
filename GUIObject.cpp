#include "GUIObject.h"


GUIObject::GUIObject(double x, double y, double w, double h):StaticObject(x,y,w,h){
}
void GUIObject::setFocus(bool stat){
	inFocus = stat;
}
bool GUIObject::isFocused(){
	return inFocus;
}
GUIObject::~GUIObject(){
	
}

