/*
Code not written by me

See GraphicFont.h for information
*/

#include "GraphicFont.h"

#include <windows.h>		// Header File For Windows


GraphicFont::GraphicFont(int size, int type){
	started = false;
	fontSize = size;
}

bool GraphicFont::init(){
	HFONT	font;										// Windows Font ID
	HFONT	oldfont;									// Used For Good House Keeping

	base = glGenLists(96);								// Storage For 96 Characters

	font = CreateFont(	-24,							// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_BOLD,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						"Courier New");					// Font Name

	oldfont = (HFONT)SelectObject(hDC, font);           // Selects The Font We Want
	wglUseFontBitmaps(hDC, 32, 96, base);				// Builds 96 Characters Starting At Character 32
	SelectObject(hDC, oldfont);							// Selects The Font We Want
	DeleteObject(font);									// Delete The Font

	started = true;
	return true;
}
//positions with top left reference
//becase loaded lists are with bottom left reference
void GraphicFont::positionFont(double x, double y){
	glRasterPos2f(x+1, y+fontSize);
}
void GraphicFont::print( const char *fmt, ... ){
	char text[256];
	va_list ap;

	if ( fmt == NULL ) return;

	va_start( ap, fmt );
		vsprintf( text, fmt, ap );
	va_end( ap );
	
	glPushAttrib( GL_LIST_BIT );
	glListBase( fontList - 32 );
	glCallLists( strlen( text ), GL_UNSIGNED_BYTE, text );
	glPopAttrib( );
}


GraphicFont::~GraphicFont(){
	glDeleteLists(fontList, 96);
}

