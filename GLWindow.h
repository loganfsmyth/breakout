#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#define RENDER_TYPE		1
#define RENDER_SDL		(Uint32)0
#define RENDER_OPENGL	(Uint32)RENDER_TYPE

#define WINDOW_TYPE		2
#define WINDOWED			(Uint32)0
#define FULLSCREEN		(Uint32)WINDOW_TYPE

#define WINDOW_BEHAVIOR	4
#define RESIZABLE			(Uint32)0
#define STATIC			(Uint32)WINDOW_BEHAVIOR

class GLWindow{
	
	public:
		GLWindow();
		~GLWindow();
		bool init(int width, int height, Uint32 params);
		void toggleFullscreen();
		bool isFullscreen();
		void hideCursor();
		void showCursor();
		void captureMouse();
		void releaseMouse();
		void setCaption(char* cap);
		void setIcon(char* filename);
		bool processWindowEvent(SDL_Event* event);
		void centerMouse();
		int getHeight();
		int getWidth();
	private:
		bool fullscreen;
		bool initializeGL(int width, int height);
		int width;
		int height;
		Uint32 params;
};
