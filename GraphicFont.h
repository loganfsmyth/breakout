/*
The Code in this class isn't mine. 
It was all copied from NeHe's (nehe.gamedev.net)
tutorial number 13. This code was taked from the SDL port
of the tutorial code by Ti Leggett

*/

#ifndef INCLUDED_FONT_H
#define INCLUDED_FONT_H

#include "SDL/SDL_opengl.h"
#include "GL/glx.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>


class GraphicFont{
	private:
		GLuint fontList;
		bool started;
		int fontSize;
		
	public:
		GraphicFont();
		bool init();
		void positionFont(double x, double y);
		void print( const char *fmt, ... );
		~GraphicFont();
};

#endif
