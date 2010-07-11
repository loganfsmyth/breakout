#ifndef INCLUDED_MENU_H
#define INCLUDED_MENU_H

#include "Button.h"
#include "TextBox.h"
#include "GUIObject.h"

class Menu: public GUIObject{
	private:
		GUIObject** objects;
		int maxSize;
		int curSize;
	public:
		Menu(int size, double x, double y, double w, double h);
		bool processMouseEvent(SDL_Event* event);
		bool processKeyboardEvent(SDL_Event* event);
		void addObject(GUIObject* obj);
		void render();
		void update();
		virtual ~Menu();
};

#endif
