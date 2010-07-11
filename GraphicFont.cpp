/*
Code not written by me

See GraphicFont.h for information
*/

#include "GraphicFont.h"

GraphicFont::GraphicFont(int size, int type){
	started = false;
	fontSize = size;
}

bool GraphicFont::init(){
	Display *dpy;
	XFontStruct *fontInfo;
	fontList = glGenLists( 96 );
	dpy = XOpenDisplay( NULL );
	char* fontStr = (char*)malloc(sizeof(char)*100);
	sprintf(fontStr, "%s%i%s", "-adobe-helvetica-medium-r-normal--", fontSize, "-*-*-*-p-*-iso8859-1");
	
//	printf(fontStr);
//	printf("\n");
//	fontInfo = XLoadQueryFont( dpy, "-adobe-helvetica-medium-r-normal--24-*-*-*-p-*-iso8859-1" );
	fontInfo = XLoadQueryFont( dpy, fontStr);
	free(fontStr);

	if ( fontInfo == NULL ){
		fontInfo = XLoadQueryFont( dpy, "fixed" );
		if ( fontInfo == NULL ){
			printf("Font: Error loading\n");
			return false;
		}
	}
	glXUseXFont( fontInfo->fid, 32, 96, fontList );
	XFreeFont( dpy, fontInfo );
	XCloseDisplay( dpy );

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

