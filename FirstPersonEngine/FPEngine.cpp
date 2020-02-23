#include "FPEngine.h"

FPEngine::FPEngine(unsigned int screenWidth, unsigned int screenHeight)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	this->projection = glm::perspective(glm::radians(45.0f), (float)this->screenWidth / (float)this->screenHeight, 0.1f, 100.0f);

	this->grid = new Grid();
	this->input = new Input();
	this->scene = new Scene(screenWidth, screenHeight);
}

FPEngine::~FPEngine()
{
	delete this->grid;
	delete this->input;
	delete this->scene;
}

void FPEngine::load()
{
}

void FPEngine::updateInput(double dt, SDL_Window* &window)
{
	/* Update event queue */
	input->update(dt);

	/* reset mouse to the center of the screen */
	SDL_WarpMouseInWindow(window, this->screenWidth / 2.0f, this->screenHeight / 2.0f);

	/* get key movements */
	if (input->isA()) this->scene->actorStrafeLeft(dt);
	if (input->isD()) this->scene->actorStrafeRight(dt);
	if (input->isW()) this->scene->actorForward(dt);
	if (input->isS()) this->scene->actorBackward(dt);

	if (input->isMouseMotion()) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		this->scene->mousePositionUpdate(dt, x, y);
	}
	if (input->isQuit()) this->quit = true;

	this->view = this->scene->viewMat4();
}

void FPEngine::updatePhysics(double dt)
{
	this->scene->update(dt);
}

void FPEngine::render()
{
	this->grid->render(this->projection, this->view, this->scene->viewPosVec3());
	this->scene->render(this->projection);
}

bool FPEngine::isQuit() { return this->quit; }
