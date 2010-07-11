#ifndef INCLUDED_GAME_H
#define INCLUDED_GAME_H
 
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
 
 #include "Log.h"
 #include "GLWindow.h"
 #include "Timer.h"
 #include "LevelData.h"
 #include "LevelList.h"
 #include "Ball.h"
 #include "Texture.h"
 #include "Paddle.h"
 #include "GraphicFont.h"
 #include "Menu.h"
 #include "Button.h"
 #include "CountdownMenu.h"
 
 #define HORIZ_RES		800
 #define VERT_RES		600
 
 #define BOTTOM_BORDER	25
 
#define GAME_FPS			40
#define GAME_LOOP_EVENT	10

#define BORDER_WIDTH		50

#define EDGE_LEFT			0
#define EDGE_RIGHT		1
#define EDGE_TOP			2
#define EDGE_BOTTOM		3

#define NUM_LIVES_INITIAL	4

#define SCORE_PER_HIT		100

#define NUM_TEXTURES		3
#define TEXTURE_BALL		0
#define TEXTURE_BLOCK		1
#define TEXTURE_PADDLE	2

#define TEXTURE_FILE_BALL		"Data/particle.bmp"
#define TEXTURE_FILE_BLOCK		"Data/particle.bmp"
#define TEXTURE_FILE_PADDLE	"Data/particle.bmp"


#define NUM_MENUS			6
#define MENU_HIDDEN			0
#define MENU_MAIN				1
#define MENU_SETTINGS			2
#define MENU_SCORE_DISPLAY	3
#define MENU_NAME_ENTER		4
#define MENU_COUNTDOWN		5

 

Log* log;
GLWindow* win;
SDL_TimerID gameloopTimer;
Timer* fpsMon;
bool running;
bool paused;

GUIObject** menus;
int currentMenu;

GraphicFont* font;

LevelList* levelList;
LevelData* currentLevel;
Ball* currentBall;
Paddle* currentPaddle;
GLuint* textures;

StaticObject** edges;

unsigned int score;
int lives;


void processKeyboardEvent(SDL_Event* event);
void processMouseEvent(SDL_Event* event);
Uint32 addGameEvent(Uint32 interval, void* param);

void resumeGame();
void startGame();
void initializeNewGame();

void processGameLogic();
void renderGame();

void renderBorder();
void renderValues();
void updateBlocks();
bool loadTextures();
void loadMenus();
void pauseGame(bool status);

void renderDarkScreen();

StaticObject** getObjects(int* numObjects);

void filterIndicies(int* indicies, int* num, int removeAbove);

void startProgram();
bool gameLoop();
void endProgram();


#endif
