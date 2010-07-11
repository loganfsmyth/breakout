#ifndef INCLUDED_MENUSCREEN_H
#define INCLUDED_MENUSCREEN_H


#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "Menu.h"


#define MENU_HIDDEN			-1
#define MENU_MAIN				0
#define MENU_SETTINGS			1
#define MENU_SCORE_DISPLAY	2
#define MENU_NAME_ENTER		3


class MenuScreen{
	private:
		Menu** menus;
		int currentMenu;
		bool enabled;
		int numMenus;
	public:
		MenuScreen(int numMenus);
		void showMenu(int menu);
		void processMouseEvent(SDL_Event* event);
		void processKeyboardEvent(SDL_Event* event);
		void update();
		void render();
		void addMenu(int position, Menu* toAdd);
		~MenuScreen();
};

#endif
