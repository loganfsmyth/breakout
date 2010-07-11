#ifndef INCLUDED_MENU_H
#define INCLUDED_MENU_H

#include "GUIObject.h"

class Menu: public GUIObject{
	public:
		Menu(int size, double x, double y, double w, double h);
		virtual ~Menu();
};

#endif
