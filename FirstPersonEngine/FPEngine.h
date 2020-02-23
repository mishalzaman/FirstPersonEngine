#ifndef FP_ENGINE
#define FP_ENGINE

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Grid.h"
#include "Input.h"
#include "Scene.h"

class FPEngine
{
	public:
		FPEngine(unsigned int screenWidth, unsigned int screenHeight);
		~FPEngine();
		void load();
		void updateInput(double dt, SDL_Window* &window);
		void updatePhysics(double dt);
		void render();
		bool isQuit();
	private:
		bool quit = false;
		unsigned int screenWidth = 0;
		unsigned int screenHeight = 0;
		Grid* grid;
		Input* input;
		Scene* scene;
		glm::mat4 projection = glm::mat4(1);
		glm::mat4 view = glm::mat4(1);

};

#endif

