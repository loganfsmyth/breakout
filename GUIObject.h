#ifndef INCLUDED_GUIOBJECT_H
#define INCLUDED_GUIOBJECT_H

#include "StaticObject.h"
#include "TexturedObject.h"


class GUIObject: public StaticObject, public TexturedObject{
	
	private:
		bool inFocus;
	public:
		GUIObject(double x, double y, double w, double h);
		virtual void render();
		virtual void update();
		void setFocus(bool stat);
		bool isFocused();
		virtual ~GUIObject();
};


#endif
