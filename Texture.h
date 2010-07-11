#ifndef INCLUDED_TEXTURE_H
#define INCLUDED_TEXTURE_H

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

class Texture{
	public:
		Texture();
		~Texture();
	
		bool loadText(char* fontname, char* text, int size, SDL_Color color, GLuint textureID);
		bool loadTextSurface(TTF_Font* font, char* text, SDL_Color color);
	
		bool loadImage(char* filename, GLuint textureID);
		bool loadImageSurface(char* filename);
	
		bool convert();
		bool bind(GLuint textureID);
		
		int getHeight();
		int getWidth();
	private:
		SDL_Surface* surface;
		bool loaded;
		int width,height;
};

#endif
