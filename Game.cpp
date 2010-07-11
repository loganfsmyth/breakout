#include "Game.h"



/*
TODO:
add particles after impacts
add dissolve effect for blocks
make menus decent
alter speed of ball based on paddle speed
potentially add items

move "move" code into a separeate physics engine file and create abstract physics object for inheriting dynamic (for use by particles)
make a particle effect object and have collisionEffect and dissolveeffect inherit from it

can change block level code because if we begin to sort the blocks based on position(for easy collision calculations
this will make it much faster to process collisions


dissolveeffect
    constructor takes x, y, w, h    maybe number of particles...probably not
    
collisionEffect
   location is all it needs
   
particleeffect  
   getParticles()
   render()
   
   
   at some point I'll have to start sorting the blocks for location in order to
   make collision faster
   
   cannot simply compare every block with every ball/particle
   will destroy performance
   
   already uses way too much processor power for a simple game


should consider making polygon, square and circle objects that can calculate overlaps with eachother


The other thing I would like to do is switch over to using pure C++, rather than a combo of C and C++

*/



int main(int argc, char** argv){
	startProgram();
	gameLoop();
	endProgram();
	
}


void startProgram(){
	bool stat;
	
	gamelog = new Log("Game.log", LOG_OVERWRITE);
	
	int error = SDL_Init(SDL_INIT_EVERYTHING);
	if(error < 0) gamelog->printLine("Failed to Initialize SDL");
	else gamelog->printLine("Initialized SDL Successfully");
	
	win = new GLWindow();
	stat = win->init(HORIZ_RES, VERT_RES, STATIC | RENDER_OPENGL);
	if(stat) gamelog->printLine("Initialized Window Successfully");
	else gamelog->printLine("Failed to Initialize Window");

	edges = (StaticObject**)malloc(sizeof(StaticObject*)*4);
	edges[EDGE_TOP] = new StaticObject(0,-BORDER_WIDTH,HORIZ_RES, BORDER_WIDTH);
	edges[EDGE_LEFT] = new StaticObject(-BORDER_WIDTH,0,BORDER_WIDTH, VERT_RES);
	edges[EDGE_BOTTOM] = new StaticObject(0,VERT_RES-BOTTOM_BORDER,HORIZ_RES, BORDER_WIDTH);
	edges[EDGE_RIGHT] = new StaticObject(HORIZ_RES,0,BORDER_WIDTH, VERT_RES);
	
	font = new GraphicFont(20);
	stat = font->init();
	if(stat) gamelog->printLine("Initialized Font Successfully");
	else gamelog->printLine("Failed to Initialize Font");
	
	levelList = new LevelList();
	stat = levelList->init();
	if(stat) gamelog->printLine("Initialized LevelList Successfully");
	else gamelog->printLine("Failed to Initialize LevelList");
	
	
	fpsMon = new Timer();
	stat = fpsMon->init();
	if(stat) gamelog->printLine("Initialized Timer Successfully");
	else gamelog->printLine("Failed to Initialize Timer");
	
	textures = (GLuint*)malloc(sizeof(GLuint)*NUM_TEXTURES);
	glGenTextures(NUM_TEXTURES,textures);
	
	stat = loadTextures();
	if(stat) gamelog->printLine("Initialized Textures Successfully");
	else gamelog->printLine("Failed to Initialize Textures");
	
	glBindTexture(GL_TEXTURE_2D, 0);

	collisions = new Collision*[MAX_NUM_COLLISIONS];
	
//	collisions = (Collision**)malloc(sizeof(Collision*)*MAX_NUM_COLLISIONS);
	int i;
	for(i = 0; i < MAX_NUM_COLLISIONS; i++) collisions[i] = NULL;

	
	loadMenus();
	
	currentLevel = NULL;
	currentBall = NULL;
	currentPaddle = NULL;

	switchMenu(MENU_MAIN);
}
void switchMenu(int type, int time, void (*func)()){
	
	if(type == MENU_COUNTDOWN){
		if(currentMenu == MENU_COUNTDOWN){
			if(func != NULL) (*func)();
			return;
		}
		
		if(menus[MENU_COUNTDOWN] != NULL) delete menus[MENU_COUNTDOWN];
		menus[MENU_COUNTDOWN] = new CountdownMenu(time, 0, 0, HORIZ_RES,VERT_RES);
		menus[MENU_COUNTDOWN]->setCallback(func);
	}
	
	menus[currentMenu]->setPaused(true);
	
	if(type == MENU_HIDDEN) pauseGame(false);
	else pauseGame(true);
	
	currentMenu = type;
	menus[currentMenu]->setPaused(false);
}

void newGame(){
	initializeNewGame();
	resumeGame();
}
void resumeGame(){
	if(lives <= 0) return;
	switchMenu(MENU_COUNTDOWN, 5000, &startGame);
}
void startGame(){
	switchMenu(MENU_HIDDEN);
}
void loadMenus(){
	GLuint* tex = (GLuint*)malloc(sizeof(GLuint)*50);
	glGenTextures(50, tex);
	
	menus = (GUIObject**)malloc(sizeof(GUIObject*)*NUM_MENUS);
	int i;
	for(i = 0; i < NUM_MENUS; i++) menus[i] = NULL;
	
	menus[MENU_HIDDEN] = new Menu(0,0.0,0.0,0.0,0.0);	//create simple empty menu
	
	menus[MENU_MAIN] = new Menu(6,350.0,150.0,150.0,300.0);
	menus[MENU_MAIN]->enableBorder();
	
	Button* bu = new Button(0.0,0.0,175.0,30.0, BUTTON_TYPE_TEXT, "Resume  Game!");
	bu->enableBorder();
	bu->setCallback(&resumeGame);
	menus[MENU_MAIN]->addObject(bu);
	
	bu = new Button(0.0,100.0,130.0,30.0, BUTTON_TYPE_TEXT, "New Game!");
	bu->enableBorder();
	bu->setCallback(&newGame);
	
	menus[MENU_MAIN]->addObject(bu);
	
	
}
void initializeLevel(){
	generateNewBall();
	generateNewPaddle();
	
	if(currentLevel != NULL) delete currentLevel;
	currentLevel = levelList->getLevel();
	
	currentLevel->regenerateBlocks(HORIZ_RES, VERT_RES-BOTTOM_BORDER);
	currentLevel->setTexture(textures[TEXTURE_BLOCK], 0.0,0.0,1.0,1.0);
}

void generateNewBall(){
	if(currentBall != NULL) delete currentBall;
	currentBall = new Ball(397.0,VERT_RES-BOTTOM_BORDER-50);
	currentBall->setTexture(textures[TEXTURE_BALL], 0.0, 0.0, 1.0, 1.0);
}
void generateNewPaddle(){
	if(currentPaddle != NULL) delete currentPaddle;
	currentPaddle = new Paddle(330.0, VERT_RES-BOTTOM_BORDER-20, 150.0);
	currentPaddle->setTexture(textures[TEXTURE_PADDLE], 0.0, 0.0, 1.0, 1.0);
}
void initializeNewGame(){
	levelList->restartLevels();
	initializeLevel();
	
	score = 0;
	lives = NUM_LIVES_INITIAL;
}	
bool loadTextures(){
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
	tex = new Texture();
	retVal = retVal && tex->loadImage(TEXTURE_FILE_PARTICLE, textures[TEXTURE_PARTICLE]);
	delete tex;
	return retVal;
}
bool gameLoop(){
	
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
			case SDL_MOUSEMOTION:
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

void processKeyboardEvent(SDL_Event* event){
	if(event->type == SDL_KEYDOWN){
		if(event->key.keysym.sym == SDLK_LEFT) currentPaddle->setMoveLeft(true);
		else if(event->key.keysym.sym == SDLK_RIGHT) currentPaddle->setMoveRight(true);
		else if(event->key.keysym.sym == SDLK_RETURN){
			if(paused) switchMenu(MENU_COUNTDOWN, 2000, &startGame);
			else switchMenu(MENU_MAIN);
			
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
void processMouseEvent(SDL_Event* event){
	menus[currentMenu]->processMouseEvent(event);
	
	
	if(event->type == SDL_MOUSEBUTTONDOWN){
//		if(event->button.button == SDL_BUTTON_LEFT) currentPaddle->setMoveLeft(true);
//		else if(event->button.button == SDL_BUTTON_RIGHT) currentPaddle->setMoveRight(true);
		
	}
	else if(event->type == SDL_MOUSEBUTTONUP){
//		if(event->button.button == SDL_BUTTON_LEFT) currentPaddle->setMoveLeft(false);
//		else if(event->button.button == SDL_BUTTON_RIGHT) currentPaddle->setMoveRight(false);
	}
	else if(event->type == SDL_MOUSEMOTION){
		
	}
	else{
		printf("Game: Mouse:: This shouldn't Happen\n");
	}
}
void pauseGame(bool status){
	if(status){
		if(currentBall != NULL) currentBall->pause();
		if(currentPaddle != NULL) currentPaddle->pause();
		paused = true;
	}
	else{
		if(currentBall != NULL) currentBall->unpause();
		if(currentPaddle != NULL) currentPaddle->unpause();
		paused = false;
	}
}

void processGameLogic(){
	
	double xShiftBall = 0, yShiftBall = 0, xShiftPaddle = 0, yShiftPaddle = 0;
	int numObjects = 0;
	int numHit = 0;
	bool hitBottom = false, hitPaddle = false;
	int scoreIncrease = 0;
	
	StaticObject** objects = getObjects(&numObjects);
	int* indicesHit = (int*)malloc(sizeof(int)*4);
	int i;
	for(i = 0; i < 4; i++) indicesHit[i] = -1;
	
	int collision = currentBall->checkForCollision(objects, numObjects, &xShiftBall, &yShiftBall, indicesHit, &numHit);
	//only need to check 2 sides because left and right are first in the edges array
	currentPaddle->checkForCollision(edges, 2, &xShiftPaddle, &yShiftPaddle);

	for(i = 0; i < numHit; i++){
		if(objects[indicesHit[i]] == edges[EDGE_BOTTOM]) hitBottom = true;
		else if(objects[indicesHit[i]] == currentPaddle) hitPaddle = true;
	}
	
	//filter out values above the number of visible blocks
	//must filter because this array also contains the edges, paddle and ball
	
	filterIndicies(indicesHit, &numHit, currentLevel->getNumVisible()-1);
	
	for(i = 0; i < numHit; i++){
		if(indicesHit[i] != -1){
			scoreIncrease += SCORE_PER_HIT;

			GLfloat r, g, b;
			
			Collision* added = addCollision(currentBall->getX()+currentBall->getW()/2, currentBall->getY()+currentBall->getH()/2);
			((Block*)objects[indicesHit[i]])->getColor(&r, &g, &b);
			
			
			added->setColor(r,g,b);
		}
	}
	
	for(i = 0; i < numCollisions;i++){
		collisions[i]->processCollisions(objects, numObjects-1);
	}
	
	currentLevel->setBlockImpact(indicesHit, numHit);
	
	double inc = 0.02;
	
	if(hitPaddle){
		if(currentBall->movingSW() && currentPaddle->movingLeft()){
			currentBall->incXVel(-1*inc);
		}
		else if(currentBall->movingSW() && currentPaddle->movingRight()){
			currentBall->incXVel(inc);
		}
		else if(currentBall->movingSE() && currentPaddle->movingLeft()){
			currentBall->incXVel(inc);
		}
		else if(currentBall->movingSE() && currentPaddle->movingRight()){
			currentBall->incXVel(-1*inc);
		}
		
		
		
	}
	
	if((collision & X_AXIS) == X_AXIS) currentBall->invertXVel();
	if((collision & Y_AXIS) == Y_AXIS) currentBall->invertYVel();
	
	currentBall->shiftX(xShiftBall);
	currentBall->shiftY(yShiftBall);
	currentPaddle->shiftX(xShiftPaddle);
	currentPaddle->shiftY(yShiftPaddle);

	currentBall->move();
	currentPaddle->move();
	for(i = 0; i < numCollisions; i++){
		collisions[i]->move();
	}
	
	
	free(indicesHit);
	free(objects);
	
	score += scoreIncrease;
	
	if(hitBottom){
		lives--;
		pauseGame(true);
		generateNewBall();
		generateNewPaddle();
		switchMenu(MENU_COUNTDOWN, 2000, &startGame);
	}
	if(lives <= 0){
		pauseGame(true);
//		currentMenu = MENU_SCORE_DISPLAY;
		switchMenu(MENU_MAIN);
	}
	else if(currentLevel->getNumVisible() <= 0){
		levelList->nextLevel();
		initializeLevel();
		pauseGame(true);
		switchMenu(MENU_COUNTDOWN, 2000,startGame);
	}
}
Collision* addCollision(double x, double y){
	if(numCollisions >= MAX_NUM_COLLISIONS) return NULL;
	
	int i;	
	for(i = 0; i < MAX_NUM_COLLISIONS; i++){
		if(collisions[i] == NULL || collisions[i]->hasFaded()){
			if(collisions[i] != NULL){
				delete collisions[i];
				collisions[i] = NULL;
				numCollisions--;
			}
			collisions[i] = new Collision(x,y);
			collisions[i]->setTexture(textures[TEXTURE_PARTICLE]);
			
			numCollisions++;
			return collisions[i];
		}
	}
	return NULL;
}


void filterIndicies(int* indices, int* num, int removeAbove){
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
StaticObject** getObjects(int* numObjects){
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
	
	//game is highly reliant on the paddle being the next object after the bottom edge, do not change
	//will affect the waythat the ball reflects off of the paddle in processGameLogic
	
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

void renderBorder(){
	
	glLoadIdentity();
	glColor3f(0.5, 0.5, 0.5);
	
	glBegin(GL_LINES);
		glVertex3f(0.0, VERT_RES-BOTTOM_BORDER+2, 0.0);
		glVertex3f(HORIZ_RES, VERT_RES-BOTTOM_BORDER+2, 0.0);
	glEnd();
	
}
void renderValues(){
	glRasterPos2f(5.0, VERT_RES-4);
	font->print("Score: %i", score);
	
	glRasterPos2f(HORIZ_RES-70, VERT_RES-4);
	font->print("Lives: %i", lives);
	
}
void renderGame(){
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	
	if(currentLevel != NULL){
//		glBlendFunc(GL_SRC_ALPHA,GL_ONE);
		int i;
		for(i = 0; i < numCollisions; i++){
			collisions[i]->render();
		}
		currentBall->render();
//		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		currentPaddle->render();
		currentLevel->render();
		renderBorder();
		renderValues();
	}
	if(currentMenu != MENU_HIDDEN){
		renderDarkScreen();
		menus[currentMenu]->render();
	}
	SDL_GL_SwapBuffers();
}
void renderDarkScreen(){
	glLoadIdentity();
	glColor4f(0.0, 0.0, 0.0, 0.4f);
	
	glBegin(GL_QUADS);
		glVertex2i(0, 0);
		glVertex2i(0, VERT_RES);
		glVertex2i(HORIZ_RES, VERT_RES);
		glVertex2i(HORIZ_RES, 0);
	glEnd();
	
}
Uint32 addGameEvent(Uint32 interval, void* param){
	// Create a user event to call the game loop.
	SDL_Event event;

	event.type = SDL_USEREVENT;
	event.user.code = GAME_LOOP_EVENT;
	event.user.data1 = 0;
	event.user.data2 = 0;

	SDL_PushEvent(&event);

	return interval;	//the return value tells the time what timeout it should use next time
}



void endProgram(){
	
	if(currentLevel != NULL) delete currentLevel;
	if(currentBall != NULL) delete currentBall;
	if(currentPaddle != NULL) delete currentPaddle;
	
	
	int i;
	for(i = 0; i < numCollisions; i++){
		delete collisions[i];
	}
//	free(collisions);
	delete[] collisions;

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
	delete gamelog;
}

