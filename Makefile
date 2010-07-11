options =  -Wall -g -ggdb
link = `sdl-config --libs` -lGLU -lSDL_image -lSDL_ttf

OBJ_FILES = Timer.o GLWindow.o Texture.o Log.o Game.o LevelData.o Ball.o Block.o StaticObject.o DynamicObject.o TexturedObject.o Paddle.o Particle.o LevelList.o GraphicFont.o GUIObject.o Menu.o Button.o CountdownMenu.o

compile: ${OBJ_FILES}
	g++ ${options} -o main ${OBJ_FILES} ${link}
run: compile
	./main
clean: 
	rm -f ${OBJ_FILES}
Game.o: Game.cpp Game.h 
	g++ ${options} -c Game.cpp	
Timer.o: Timer.cpp Timer.h
	g++ ${options} -c Timer.cpp
GLWindow.o: GLWindow.cpp GLWindow.h
	g++ ${options} -c GLWindow.cpp
Texture.o: Texture.cpp Texture.h
	g++ ${options} -c Texture.cpp
Log.o: Log.cpp Log.h
	g++ ${options} -c Log.cpp
GraphicFont.o: GraphicFont.cpp GraphicFont.h
	g++ ${options} -c GraphicFont.cpp
LevelData.o: LevelData.cpp LevelData.h Block.o
	g++ ${options} -c LevelData.cpp
LevelList.o: LevelList.cpp LevelList.h LevelData.o
	g++ ${options} -c LevelList.cpp
	
Ball.o: Ball.cpp Ball.h DynamicObject.o
	g++ ${options} -c Ball.cpp
Block.o: Block.cpp Block.h StaticObject.o
	g++ ${options} -c Block.cpp
Paddle.o: Paddle.cpp Paddle.h DynamicObject.o
	g++ ${options} -c Paddle.cpp
Particle.o: Particle.cpp Particle.h DynamicObject.o
	g++ ${options} -c Particle.cpp
	
StaticObject.o: StaticObject.cpp StaticObject.h
	g++ ${options} -c StaticObject.cpp
DynamicObject.o: DynamicObject.cpp DynamicObject.h
	g++ ${options} -c DynamicObject.cpp
TexturedObject.o: TexturedObject.cpp TexturedObject.h
	g++ ${options} -c TexturedObject.cpp
GUIObject.o: GUIObject.cpp GUIObject.h
	g++ ${options} -c GUIObject.cpp
Menu.o: Menu.cpp Menu.h
	g++ ${options} -c Menu.cpp
CountdownMenu.o: CountdownMenu.cpp CountdownMenu.h
	g++ ${options} -c CountdownMenu.cpp
Button.o: Button.cpp Button.h
	g++ ${options} -c Button.cpp
