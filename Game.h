#ifndef INCLUDED_GAME_H
#define INCLUDED_GAME_H
 
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
 
 #include "Log.h"
 #include "Window.h"
 #include "Timer.h"
 #include "Level.h"
 #include "Ball.h"
 #include "Texture.h"
 
 #define HORIZ_RES		800
 #define VERT_RES		600
 
#define GAME_FPS			60
#define GAME_LOOP_EVENT	10

#define PAST_X_EDGE		1
#define PAST_Y_EDGE		2


#define NUM_TEXTURES		3
#define TEXTURE_BALL		0
#define TEXTURE_BLOCK		1
#define TEXTURE_PADDLE	2

#define TEXTURE_FILE_BALL		"Data/particle.bmp"
#define TEXTURE_FILE_BLOCK		"Data/particle.bmp"
#define TEXTURE_FILE_PADDLE	"Data/particle.bmp"

 
class Game{
	private:
		Log* log;
		Window* win;
		SDL_TimerID gameloopTimer;
		Timer* fpsMon;
		bool running;
		Level* currentLevel;
		Ball* currentBall;
		GLuint* textures;
		
		bool displayMenu;
		
		void processKeyboardEvent(SDL_Event* event);
		void processMouseEvent(SDL_Event* event);
		static Uint32 addGameEvent(Uint32 interval, void* param);
	
		void processGameLogic();
		void renderGame();
	
		void updateBlocks();
	
		bool loadTextures();
		
	
	public:
		Game();
		bool gameLoop();
		~Game();
};

#endif
