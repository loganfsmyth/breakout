#include "Game.h"

int main(int argc, char** argv){

	Game* game = new Game();
	game->gameLoop();	
	delete game;
	
	return 0;
}
