#include "MenuScreen.h"

MenuScreen::MenuScreen(int numMenus){
	this->numMenus = numMenus;
	menus = (Menu**)malloc(sizeof(Menu*)*numMenus);
	int i;
	for(i = 0; i < numMenus; i++) menus[i] = NULL;
	
}
void MenuScreen::showMenu(int menu){
	if(menu >= numMenus){
		printf("MenuScreen: Error Showing Menu\n");
		return;
	}
	currentMenu = menu;	
}
void MenuScreen::processMouseEvent(SDL_Event* event){
	if(currentMenu == MENU_HIDDEN) return;
	menus[currentMenu]->processMouseEvent(event);
}
void MenuScreen::processKeyboardEvent(SDL_Event* event){
	if(currentMenu == MENU_HIDDEN) return;
	menus[currentMenu]->processKeyboardEvent(event);
}
void MenuScreen::update(){
	if(currentMenu == MENU_HIDDEN) return;
	menus[currentMenu]->update();
}
void MenuScreen::render(){
	if(currentMenu == MENU_HIDDEN) return;
	menus[currentMenu]->render();
}

void MenuScreen::addMenu(int position, Menu* menu){
	if(position >= numMenus){
		printf("MenuScreen: Error Adding Menu\n");
		return;
	}
	menus[position] = menu;
}

MenuScreen::~MenuScreen(){
	int i;
	for(i = 0; i < numMenus; i++){
		if(menus[i] != NULL) delete menus[i];
	}
	
	free(menus);
}
