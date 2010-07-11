#include "Game.h"


Game::Game(){
	bool stat;
	
	log = new Log("Game.log", LOG_OVERWRITE);
	
//	int error = SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);	//SDL_EVERYTHING
	int error = SDL_Init(SDL_INIT_EVERYTHING);
	if(error < 0) log->printLine("Failed to Initialize SDL");
	else log->printLine("Initialized SDL Successfully");
	
	win = new GLWindow();
	stat = win->init(HORIZ_RES, VERT_RES, STATIC | RENDER_OPENGL);
	if(stat) log->printLine("Initialized Window Successfully");
	else log->printLine("Failed to Initialize Window");

	edges = (StaticObject**)malloc(sizeof(StaticObject*)*4);
	edges[EDGE_TOP] = new StaticObject(0,-BORDER_WIDTH,HORIZ_RES, BORDER_WIDTH);
	edges[EDGE_LEFT] = new StaticObject(-BORDER_WIDTH,0,BORDER_WIDTH, VERT_RES);
	edges[EDGE_BOTTOM] = new StaticObject(0,VERT_RES-BOTTOM_BORDER,HORIZ_RES, BORDER_WIDTH);
	edges[EDGE_RIGHT] = new StaticObject(HORIZ_RES,0,BORDER_WIDTH, VERT_RES);
	
	font = new GraphicFont();
	stat = font->init();
	if(stat) log->printLine("Initialized Font Successfully");
	else log->printLine("Failed to Initialize Font");
	
	levelList = new LevelList();
	stat = levelList->init();
	if(stat) log->printLine("Initialized LevelList Successfully");
	else log->printLine("Failed to Initialize LevelList");
	
	
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
	
	loadMenus();
	
	currentLevel = NULL;
	currentBall = NULL;
	currentPaddle = NULL;
	
	currentMenu = MENU_HIDDEN;
	
	initializeNewGame();
	
	
	pauseGame(true);
	currentMenu = MENU_MAIN;
}
void Game::loadMenus(){
	GLuint* tex = (GLuint*)malloc(sizeof(GLuint)*50);
	glGenTextures(50, tex);
	
	menus = (Menu**)malloc(sizeof(Menu*)*NUM_MENUS);
	menus[MENU_HIDDEN] = new Menu(0,0.0,0.0,0.0,0.0);	//create simple empty menu
	
	menus[MENU_MAIN] = new Menu(1,350.0,150.0,100.0,300.0);
	
	Button* bu = new Button(0.0,0.0,130.0,30.0, BUTTON_TYPE_TEXT, "New Game!");
	menus[MENU_MAIN]->addObject(bu);
	
	
}

void Game::initializeNewGame(){
	
	currentBall = new Ball(397.0,VERT_RES-BOTTOM_BORDER-50);
	currentPaddle = new Paddle(330.0, VERT_RES-BOTTOM_BORDER-20, 200.0);
	currentLevel = levelList->getNext();
	currentLevel->regenerateBlocks(HORIZ_RES, VERT_RES-BOTTOM_BORDER);
	
	score = 0;
	lives = NUM_LIVES_INITIAL;
	
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
	retVal = retVal && tex->loadImage(TEXTURE_FILE_PADDLE, textures[TEXTURE_PADDLE]);
	delete tex;
	return retVal;
}
bool Game::gameLoop(){
	
	SDL_Event event;
	running = true;
	
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
//			case SDL_MOUSEMOTION:
				processMouseEvent(&event);
				break;
			case SDL_USEREVENT:
				
				if(!paused) processGameLogic();
				else menus[currentMenu]->update();
				
				
				renderGame();
				break;
			default:
				break;
		}   // End switch
		
		
	}   // End while
	
	return true;
}

void Game::processKeyboardEvent(SDL_Event* event){
	if(event->type == SDL_KEYDOWN){
		if(event->key.keysym.sym == SDLK_LEFT) currentPaddle->setMoveLeft(true);
		else if(event->key.keysym.sym == SDLK_RIGHT) currentPaddle->setMoveRight(true);
		else if(event->key.keysym.sym == SDLK_RETURN){
			if(paused) pauseGame(false);
			else pauseGame(true);
		}
	}
	else if(event->type == SDL_KEYUP){
		if(event->key.keysym.sym == SDLK_LEFT) currentPaddle->setMoveLeft(false);
		else if(event->key.keysym.sym == SDLK_RIGHT) currentPaddle->setMoveRight(false);
	}
	else{
		printf("Game: Keyboard:: This shouldn't Happen\n");
	}
}
void Game::processMouseEvent(SDL_Event* event){
	
	if(event->type == SDL_MOUSEBUTTONDOWN){
		if(event->button.button == SDL_BUTTON_LEFT) currentPaddle->setMoveLeft(true);
		else if(event->button.button == SDL_BUTTON_RIGHT) currentPaddle->setMoveRight(true);
		
	}
	else if(event->type == SDL_MOUSEBUTTONUP){
		if(event->button.button == SDL_BUTTON_LEFT) currentPaddle->setMoveLeft(false);
		else if(event->button.button == SDL_BUTTON_RIGHT) currentPaddle->setMoveRight(false);
	}
	else{
		printf("Game: Mouse:: This shouldn't Happen\n");
	}
}
void Game::pauseGame(bool status){
	if(status){
		currentBall->pause();
		currentPaddle->pause();
		paused = true;
		currentMenu = MENU_MAIN;
	}
	else{
		currentBall->unpause();
		currentPaddle->unpause();
		paused = false;
		currentMenu = MENU_HIDDEN;
	}
}

void Game::processGameLogic(){
	
	double xShiftBall = 0, yShiftBall = 0, xShiftPaddle = 0, yShiftPaddle = 0;
	int numObjects = 0;
	int numHit = 0;
	bool hitBottom = false;
	int scoreIncrease = 0;
	
	StaticObject** objects = getObjects(&numObjects);
	int* indicesHit = (int*)malloc(sizeof(int)*4);
	
	int collision = currentBall->checkForCollision(objects, numObjects, &xShiftBall, &yShiftBall, indicesHit, &numHit);
	//only need to check 2 sides because left and right are first in the edges array
	currentPaddle->checkForCollision(edges, 2, &xShiftPaddle, &yShiftPaddle);
	int i;
	for(i = 0; i < numHit; i++){
		if(objects[indicesHit[i]] == edges[EDGE_BOTTOM]) hitBottom = true;
	}
	
	//filter values above the number of unhidden blocks
	//must filter because this array also contains the edges, paddle and ball
	filterIndicies(indicesHit, &numHit, currentLevel->getNumVisible()-1);
	currentLevel->setBlockImpact(indicesHit, numHit);
	for(i = 0; i < numHit; i++){
		if(indicesHit[i] != -1) scoreIncrease += SCORE_PER_HIT;
	}
	
	
	if((collision & X_AXIS) == X_AXIS) currentBall->invertXVel();
	if((collision & Y_AXIS) == Y_AXIS) currentBall->invertYVel();
	
	currentBall->shiftX(xShiftBall);
	currentBall->shiftY(yShiftBall);
	currentPaddle->shiftX(xShiftPaddle);
	currentPaddle->shiftY(yShiftPaddle);

	currentBall->move();
	currentPaddle->move();
	
	free(indicesHit);
	free(objects);
	
	score += scoreIncrease;
	
	if(hitBottom) lives--;
		
	if(lives <= 0){
		pauseGame(true);
		currentMenu = MENU_SCORE_DISPLAY;
	}
}
void Game::filterIndicies(int* indices, int* num, int removeAbove){
	int i, j;
	int numNegatives = 0;
	int numValues = 0;
	int* newList = (int*)malloc(sizeof(int)*(*num));
	for(i = 0; i < (*num); i++){
		if(indices[i] == -1 || indices[i] > removeAbove){
			numNegatives++;
			newList[*num-numNegatives] = -1;
		}
		else{
			for(j = i+1; j < *num; j++){
				if(indices[i] == indices[j]) indices[j] = -1;
			}
			newList[numValues] = indices[i];
			numValues++;
		}

	}
	for(i = 0; i < (*num); i++){
		indices[i] = newList[i];
	}
	free(newList);
	
	*num = numValues;
}
StaticObject** Game::getObjects(int* numObjects){
	int numBlocks = 0;
	StaticObject** blocks = NULL;
	if(currentLevel != NULL){
		blocks = (StaticObject**)currentLevel->getBlocks(&numBlocks);
	}
	//space for blocks, plus 4 edges, the paddle, and the ball
	StaticObject** objects = (StaticObject**)malloc(sizeof(StaticObject*)*(numBlocks + 6));
	
	int i;
	for(i = 0; i < numBlocks; i++){
		objects[i] = blocks[i];
	}
	objects[i] = edges[EDGE_LEFT];
	objects[i+1] = edges[EDGE_RIGHT];
	objects[i+2] = edges[EDGE_TOP];
	objects[i+3] = edges[EDGE_BOTTOM];
	
	(*numObjects) = numBlocks+4;
	
	if(currentPaddle != NULL){
		objects[*numObjects] = (StaticObject*)currentPaddle;
		(*numObjects)++;
	}
	if(currentBall != NULL){
		objects[*numObjects] = (StaticObject*)currentBall;
		(*numObjects)++;
	}
	
	return objects;
}

void Game::renderBorder(){
	
	glLoadIdentity();
	glColor3f(0.5, 0.5, 0.5);
	
	glBegin(GL_LINES);
		glVertex3f(0.0, VERT_RES-BOTTOM_BORDER+2, 0.0);
		glVertex3f(HORIZ_RES, VERT_RES-BOTTOM_BORDER+2, 0.0);
	glEnd();
	
}
void Game::renderValues(){
	glRasterPos2f(5.0, VERT_RES-4);
	font->print("Score: %i", score);
	
	glRasterPos2f(HORIZ_RES-70, VERT_RES-4);
	font->print("Lives: %i", lives);
	
}
void Game::renderGame(){
	
	
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	renderBorder();
	renderValues();
	currentLevel->render();
	currentBall->render();
	currentPaddle->render();
	
	if(currentMenu != MENU_HIDDEN){
		renderDarkScreen();
		menus[currentMenu]->render();
	}
	SDL_GL_SwapBuffers();
}
void Game::renderDarkScreen(){
	glLoadIdentity();
	glColor4f(0.0, 0.0, 0.0, 0.4f);
	
	glBegin(GL_QUADS);
		glVertex2i(0, 0);
		glVertex2i(0, VERT_RES);
		glVertex2i(HORIZ_RES, VERT_RES);
		glVertex2i(HORIZ_RES, 0);
	glEnd();
	
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
	if(currentPaddle != NULL) delete currentPaddle;
	
	
	delete edges[0];
	delete edges[1];
	delete edges[2];
	delete edges[3];
	free(edges);
	
	glDeleteTextures(NUM_TEXTURES, textures);
	free(textures);
	
	SDL_RemoveTimer(gameloopTimer);
	SDL_Quit();
	
	
	delete levelList;
	delete fpsMon;
	delete win;
	delete log;
}

