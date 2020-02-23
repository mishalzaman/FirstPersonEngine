#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "SysSdlOpenGL.h"
#include "SysOpenGLSetting.h"
#include "FPEngine.h"

SDL_Window* window;
SDL_GLContext context;
unsigned int SCREEN_WIDTH = 640;
unsigned int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]) {
	/*--------------------------
	OPENGL / SDL INITIALIZATION
	---------------------------*/
	if (unsigned int errCode = SysSdlOpenGL::defaults(window, context, SCREEN_WIDTH, SCREEN_HEIGHT, 3, 3) > 0) return errCode;
	SysOpenGLSetting::defaults(window, SCREEN_WIDTH, SCREEN_HEIGHT);

	/*--------------
	INITIALIZATIONS
	--------------*/
	FPEngine* fpEngine = new FPEngine(SCREEN_WIDTH, SCREEN_HEIGHT);

	fpEngine->load();

	double dt = 1.0f / 60.0f;

	while (!fpEngine->isQuit()) {
		fpEngine->updateInput(dt, window);
		fpEngine->updatePhysics(dt);
		fpEngine->render();
		SysOpenGLSetting::swapBuffers(window, SCREEN_WIDTH, SCREEN_HEIGHT);
	}

	delete fpEngine;
	return SysSdlOpenGL::shutDown(window, context);
}