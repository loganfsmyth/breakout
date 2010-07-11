#include "Game.h"

//todo:
/* find out if when you pass an Event into the queue, it is copied, or if it is just put into the queue
this will cause issues with my mallocing if it is not corret


*/


Game::Game(){
	bool stat;
	
	log = new Log("Game.log", LOG_OVERWRITE);
	
	int error = SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);	//SDL_EVERYTHING
	if(error < 0) log->printLine("Failed to Initialize SDL");
	else log->printLine("Initialized SDL Successfully");
	
	win = new Window();
	stat = win->init(HORIZ_RES, VERT_RES, STATIC | RENDER_OPENGL);
	if(stat) log->printLine("Initialized Window Successfully");
	else log->printLine("Failed to Initialize Window");

	glLoadIdentity();
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	
	fpsMon = new Timer();
	stat = fpsMon->init();
	if(stat) log->printLine("Initialized Timer Successfully");
	else log->printLine("Failed to Initialize Timer");
	
	textures = (GLuint*)malloc(sizeof(GLuint)*NUM_TEXTURES);
	glGenTextures(NUM_TEXTURES,textures);
	
	stat = loadTextures();
	if(stat) log->printLine("Initialized Textures Successfully");
	else log->printLine("Failed to Initialize Textures");
	
	glBindTexture(GL_TEXTURE_2D, 0);
	
	currentLevel = NULL;
	currentBall = NULL;
	displayMenu = true;
}
bool Game::loadTextures(){
	bool retVal = true;
	Texture* tex = new Texture();
	retVal = retVal && tex->loadImage(TEXTURE_FILE_BALL, textures[TEXTURE_BALL]);
	delete tex;
	tex = new Texture();
	retVal = retVal && tex->loadImage(TEXTURE_FILE_BLOCK, textures[TEXTURE_BLOCK]);
	delete tex;
	tex = new Texture();
	retVal = retVal &&  tex->loadImage(TEXTURE_FILE_PADDLE, textures[TEXTURE_PADDLE]);
	delete tex;
	return retVal;
}
bool Game::gameLoop(){
	
	SDL_Event event;
	running = true;
//	int i = 0;
	
//	addGameEvent(0,NULL);
	
	gameloopTimer = SDL_AddTimer(1000/GAME_FPS, addGameEvent, NULL);
	
	fpsMon->start();
	
	while(running && (SDL_WaitEvent(&event))) {
		
		
		switch(event.type) {
			case SDL_VIDEORESIZE:
				win->processWindowEvent(&event);
				break;
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				processKeyboardEvent(&event);
				break;
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEMOTION:
				processMouseEvent(&event);
				break;
			case SDL_USEREVENT:
				
				processGameLogic();
				renderGame();

				break;
			default:
				break;
		}   // End switch
		
		
	}   // End while
	
	return true;
}

void Game::processKeyboardEvent(SDL_Event* event){
	
	
}
void Game::processMouseEvent(SDL_Event* event){
	
	
	
}

void Game::processGameLogic(){
	bool reflectX = false;
	bool reflectY = false;
	
//	printf("_______________________\n");
	
	if(currentBall != NULL){
		
//		Rect* ballRect = currentBall->getRect();
		
/*		
		Rect* winRect = new Rect(0.0,0.0, (double)HORIZ_RES, (double)VERT_RES);
		
		if(!ballRect->nOverlap(winRect) || !ballRect->sOverlap(winRect)){
			reflectY = true;
		}
		if(!ballRect->eOverlap(winRect) || !ballRect->wOverlap(winRect)){
			reflectX = true;
		}
		delete winRect;
*/
		
		if(currentBall->getX()+currentBall->getW() > HORIZ_RES){
			reflectX = true;
			currentBall->shiftX(currentBall->getX()-HORIZ_RES);
		}
		else if(currentBall->getX() < 0){
			reflectX = true;
			currentBall->shiftX(-1*currentBall->getX());
		}
		
		if(currentBall->getY()+currentBall->getH() > VERT_RES){
			reflectY = true;
			currentBall->shiftY(currentBall->getY()-VERT_RES);
		}
		else if(currentBall->getY() < 0){
			reflectY = true;
			currentBall->shiftY(-1*currentBall->getY());
		}
		
		int xShift = 0, yShift = 0;
/*
		if(currentLevel != NULL){
//			int collision = currentLevel->checkForCollision(currentBall, &xShift, &yShift);
			int collision = currentBall->checkForCollision(arrr, size);
			if(!reflectX) reflectX = ((collision & X_AXIS) == X_AXIS);
			if(!reflectY) reflectY = ((collision & Y_AXIS) == Y_AXIS);
		}
*/
		
		if(reflectX) currentBall->invertXVel();
		if(reflectY) currentBall->invertYVel();
		
		currentBall->shiftX(xShift);
		currentBall->shiftY(yShift);
		
		currentBall->move();
	}
}

void Game::renderGame(){
	displayMenu = false;
	
	
	glLoadIdentity();
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BALL]);
	
	if(displayMenu){
		
		
	}
	else{
		if(currentLevel == NULL){
			currentBall = new Ball(397.0,500.0);
			currentBall->enableTexture();
			
			currentLevel = new Level();
			currentLevel->open("Levels/L1.lvl");
			currentLevel->regenerateBlocks(HORIZ_RES, VERT_RES);
			
			updateBlocks();
		}
		else{
			currentLevel->render();
			currentBall->render();
		}
	}
	SDL_GL_SwapBuffers();
}

void Game::updateBlocks(){
	
	
}



Uint32 Game::addGameEvent(Uint32 interval, void* param){
	// Create a user event to call the game loop.
	SDL_Event event;

	event.type = SDL_USEREVENT;
	event.user.code = GAME_LOOP_EVENT;
	event.user.data1 = 0;
	event.user.data2 = 0;

	SDL_PushEvent(&event);

	return interval;	//the return value tells the time what timeout it should use next time
}



Game::~Game(){
	
	if(currentLevel != NULL) delete currentLevel;
	if(currentBall != NULL) delete currentBall;
	
	glDeleteTextures(NUM_TEXTURES, textures);
	
	free(textures);
	
	SDL_RemoveTimer(gameloopTimer);
	SDL_Quit();
	
	delete fpsMon;
	delete win;
	delete log;
}

