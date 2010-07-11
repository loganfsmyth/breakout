#include "Window.h"

Window::Window(){
	
	
}
Window::~Window(){
	
	
	
}
bool Window::init(int width, int height, Uint32 params){
	printf("Init window (%dx%d)\n", width, height);
	
	this->width = width;
	this->height = height;
	this->params = params;
	
	//probable not supposed to call these if not using OpenGL
	if((params & RENDER_TYPE) == RENDER_OPENGL){
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	}
	Uint32 flags = 0;
	
	if((params & WINDOW_TYPE) == FULLSCREEN) flags |= SDL_FULLSCREEN;
	if((params & WINDOW_BEHAVIOR) == RESIZABLE) flags |= SDL_RESIZABLE;
	if((params & RENDER_TYPE) == RENDER_SDL) flags |= SDL_SWSURFACE;
	else flags |= SDL_OPENGL;
	
	SDL_Surface* drawContext = SDL_SetVideoMode(width, height, 0, flags);
	if(drawContext == NULL){
		SDL_Quit();
		return false;
	}
	
	if((params & RENDER_TYPE) == RENDER_OPENGL) return initializeGL(width, height);
	else return true;
}
bool Window::initializeGL(int width, int height){
	glClearColor( 0, 0, 0, 0 );
	glEnable(GL_TEXTURE_2D);
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0, width, height, 0, -1, 1 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	
//	glShadeModel(GL_SMOOTH);
	
	glViewport( 0, 0, ( GLint )width, ( GLint )height );
	
	if( glGetError() != GL_NO_ERROR ) return false;
	else return true;
	
}
void Window::setCaption(char* cap){
	SDL_WM_SetCaption(cap, NULL );
}
void Window::setIcon(char* filename){
	//technically only uses a surface, so file doesn't NEED to be a bmp
	SDL_WM_SetIcon(SDL_LoadBMP(filename), NULL);	//windows icons must be 32x32 bmp files
}

bool Window::processWindowEvent(SDL_Event* event){
	init(event->resize.w, event->resize.h, params);
	width = event->resize.w;
	height = event->resize.h;
	return true;
}

void Window::toggleFullscreen(){
	//this seems to make everything explode, probably a bad plan
	//ends up setting the res to full screen res and then
	//it can't come back to an old windowed res
	if(isFullscreen()){
		params &= ~FULLSCREEN;
		init(width, height, params);
	}
	else{
		params |= FULLSCREEN;
		init(width, height, params);
	}
}
bool Window::isFullscreen(){
	if((params & FULLSCREEN) == FULLSCREEN) return true;
	else return false;
}
void Window::showCursor(){
	SDL_ShowCursor(SDL_ENABLE);
}
void Window::hideCursor(){
	SDL_ShowCursor(SDL_DISABLE);
}
void Window::captureMouse(){
	SDL_WM_GrabInput(SDL_GRAB_ON);
}
void Window::releaseMouse(){
	SDL_WM_GrabInput(SDL_GRAB_OFF);
}
void Window::centerMouse(){
	SDL_WarpMouse(width/2, height/2);
}
int Window::getHeight(){
	return height;
}
int Window::getWidth(){
	return width;
}
