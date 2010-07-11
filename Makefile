options =  -Wall -g -ggdb
link = `sdl-config --libs` -lGLU -lSDL_image -lSDL_ttf

OBJ_FILES = Main.o Timer.o Window.o Texture.o Log.o Game.o Level.o Ball.o Block.o Rect.o


compile: ${OBJ_FILES}
	g++ ${options} -o main ${OBJ_FILES} ${link}
run: compile
	./main
clean: 
	rm -f ${OBJ_FILES}
Main.o: Main.cpp
	g++ ${options} -c Main.cpp
Game.o: Game.cpp Game.h
	g++ ${options} -c Game.cpp	
Timer.o: Timer.cpp Timer.h
	g++ ${options} -c Timer.cpp
Window.o: Window.cpp Window.h
	g++ ${options} -c Window.cpp
Texture.o: Texture.cpp Texture.h
	g++ ${options} -c Texture.cpp
Log.o: Log.cpp Log.h
	g++ ${options} -c Log.cpp
Level.o: Level.cpp Level.h
	g++ ${options} -c Level.cpp
Ball.o: Ball.cpp Ball.h
	g++ ${options} -c Ball.cpp
Block.o: Block.cpp Block.h
	g++ ${options} -c Block.cpp
Rect.o: Rect.cpp Rect.h
	g++ ${options} -c Rect.cpp