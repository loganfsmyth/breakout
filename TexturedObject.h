#ifndef INCLUDED_TEXTUREDOBJECT_H
#define INCLUDED_TEXTUREDOBJECT_H

#include "SDL/SDL_opengl.h"
#include "Texture.h"

class TexturedObject{
	private:
		bool textured;
		bool loaded;
		GLuint tex;	//allow overriding for static value;
	public:
		TexturedObject();
		bool isTextured();
		void setTexture(GLuint newTex, double x, double y, double w, double h);
		void bindTexture();
		void unbindTexture();
		virtual ~TexturedObject();
	
};

#endif

