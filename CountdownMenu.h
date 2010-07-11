#ifndef INCLUDED_COUNTDOWNMENU_H
#define INCLUDED_COUNTDOWNMENU_H

#include "GUIObject.h"
#include "GraphicFont.h"

class CountdownMenu: public GUIObject{
	private:
		GraphicFont* font;
		float count;
		int target;
	public:
		CountdownMenu(int size, double x, double y, double w, double h);
		
		void update();
		void render();
		
		virtual ~CountdownMenu();
};

#endif
