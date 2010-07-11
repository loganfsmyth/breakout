#include "TexturedObject.h"

TexturedObject::TexturedObject(){
	textured = false;
}

bool TexturedObject::isTextured(){
	return textured;
}
void TexturedObject::setTexture(GLuint newTex, double x, double y, double w, double h){
	textured = true;
	tex = newTex;
}
void TexturedObject::bindTexture(){
	if(textured) glBindTexture(GL_TEXTURE_2D, tex);
}
void TexturedObject::unbindTexture(){
	glBindTexture(GL_TEXTURE_2D, 0);
}
TexturedObject::~TexturedObject(){
}

