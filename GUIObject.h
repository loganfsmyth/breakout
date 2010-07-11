#ifndef INCLUDED_GUIOBJECT_H
#define INCLUDED_GUIOBJECT_H

#include "StaticObject.h"
#include "TexturedObject.h"
#include "Timer.h"


class GUIObject: public StaticObject, public TexturedObject{
	
	protected:
		bool inFocus;
		GUIObject** objects;
		int maxSize;
		int curSize;
		float glow, glowFactor;
		Timer* timer;
		void (*callback)();
		bool showBorder;
		bool active;
	
	public:
		GUIObject(int numItems, double x, double y, double w, double h);
		virtual void render();
		virtual void update();
		void setFocus(bool stat);
		void setActive(bool stat);
		bool isFocused();
		bool isActive();
	
		void setPaused(bool stat);
	
		void enableBorder();
		void setCallback(void (*func)());
	
		virtual bool processMouseEvent(SDL_Event* event);
		virtual bool processKeyboardEvent(SDL_Event* event);
		void addObject(GUIObject* obj);
		virtual ~GUIObject();
};


#endif
