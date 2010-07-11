#include "Texture.h"

Texture::Texture(){
	loaded = false;
	surface = NULL;
}
Texture::~Texture(){
	if(loaded) SDL_FreeSurface(surface);
}
bool Texture::loadImageSurface(char* filename){
	if(loaded) return false;
		
	surface = IMG_Load(filename);
	if(surface == NULL){
		printf("Unable to load texture from: %s\n", filename);
		return false;
	}
	else{
//		printf("Loaded texture from: %s\n", filename);
		width = surface->w;
		height = surface->h;
		loaded = true;
		return true;
	}
}
bool Texture::loadImage(char* filename, GLuint textureID){
	if(loadImageSurface(filename)){
		bind(textureID);
		return true;
	}
	else return false;
}
bool Texture::loadTextSurface(TTF_Font* font, char* text, SDL_Color color){
	surface = TTF_RenderText_Solid(font, text, color);
	if(surface == NULL){
		printf("Unable to render font for \"%s\"\n", text);
		return false;
	}
	else{
		printf("Rendered font for \"%s\"\n", text);
		width = surface->w;
		height = surface->h;
		loaded = true;
		return true;
	}
	
	
}
bool Texture::loadText(char* fontname, char* text, int size, SDL_Color color, GLuint textureID){
	TTF_Font* font = TTF_OpenFont(fontname, size);
	if(font == NULL){
		printf("Unable to load font from: %s\n",fontname);
		return false;
	}
	bool temp = loadTextSurface(font, text,color);
	TTF_CloseFont(font);
	if(temp){
		bind(textureID);
		return true;
	}
	else return false;
	
}

bool Texture::convert(){
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		Uint32 rmask = 0xff000000;
		Uint32 gmask = 0x00ff0000;
		Uint32 bmask = 0x0000ff00;
		Uint32 amask = 0x000000ff;
	#else
		Uint32 rmask = 0x000000ff;
		Uint32 gmask = 0x0000ff00;
		Uint32 bmask = 0x00ff0000;
		Uint32 amask = 0xff000000;
	#endif

	SDL_Surface* tmpSur = SDL_CreateRGBSurface(SDL_SWSURFACE, 0, 0, 32, rmask, gmask, bmask, amask);
	
	SDL_Surface* newTex;
	newTex = SDL_ConvertSurface(surface, tmpSur->format, surface->flags);
	SDL_FreeSurface(tmpSur);
	if(newTex == NULL){
		printf("Unable to convert texture\n");
		return false;
	}
	else{
		SDL_FreeSurface(surface);
		surface = newTex;
		newTex = NULL;
		return true;
	}
}


bool Texture::bind(GLuint textureID){
	convert();
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	
	return true;
}
int Texture::getHeight(){
	return height;
}
int Texture::getWidth(){
	return width;
}

