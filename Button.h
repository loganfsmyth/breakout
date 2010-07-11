#ifndef INCLUDED_BUTTON_H
#define INCLUDED_BUTTON_H


#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "StaticObject.h"
#include "Texture.h"
#include "TexturedObject.h"
#include "GraphicFont.h"
#include "Timer.h"
#include "GUIObject.h"

#define BUTTON_TYPE_TEXT	1
#define BUTTON_TYPE_IMAGE	2

#define BUTTON_GLOW_CHANGE	0.004

class Button: public GUIObject{
	private:
		char* text;
		int type;
		GraphicFont* font;
	public:
		Button(double x, double y, double w, double h, int type, char* text = NULL);
		void render();
		void update();
		~Button();
};

#endif
