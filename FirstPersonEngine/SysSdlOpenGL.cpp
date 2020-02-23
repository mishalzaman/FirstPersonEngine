#include "SysSdlOpenGL.h"

int SysSdlOpenGL::initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return SysSdlOpenGL::ERROR_SDL_INIT;
	}

	return 0;
}

int SysSdlOpenGL::defaults(SDL_Window*& window, SDL_GLContext& context, unsigned int screenWidth, unsigned int screenHeight, unsigned int sMinor, unsigned int sMajor)
{
	unsigned int engineError;

	if (engineError = SysSdlOpenGL::initSDL() > 0) return engineError;
	if (engineError = SysSdlOpenGL::setGlAttributes(sMinor, sMajor) > 0) return engineError;
	// SysSdlOpenGL::initMultisampling(1,4);
	if (engineError = SysSdlOpenGL::initWindow(window, screenWidth, screenHeight) > 0) return engineError;
	if (engineError = SysSdlOpenGL::initContext(context, window) > 0) return engineError;
	if (engineError = SysSdlOpenGL::initGlew() > 0) return engineError;
}

int SysSdlOpenGL::setGlAttributes(unsigned int major, unsigned int minor)
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	return 0;
}

void SysSdlOpenGL::initMultisampling(int buffers, int sampleSize)
{
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, buffers);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, sampleSize);
}

int SysSdlOpenGL::initWindow(SDL_Window*& window, unsigned int width, unsigned int height)
{
	window = SDL_CreateWindow(
		"Terrain Engine",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
	);

	if (!window) {
		return SysSdlOpenGL::ERROR_CREATE_WINDOW;
	}
	return 0;
}

int SysSdlOpenGL::initContext(SDL_GLContext& context, SDL_Window*& window)
{
	context = SDL_GL_CreateContext(window);

	if (!context) {
		return SysSdlOpenGL::ERROR_CREATE_CONTEXT;
	}
	return 0;
}

int SysSdlOpenGL::initGlew()
{
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	if (err) {
		return SysSdlOpenGL::ERROR_GLEW_INIT;
	}

	return 0;
}

int SysSdlOpenGL::shutDown(SDL_Window*& window, SDL_GLContext& context)
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}