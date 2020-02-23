#include "Actor.h"

Actor::Actor(int& screenWidth, int& screenHeight, glm::vec3 position)
{
	this->view = new CameraFP(screenWidth, screenHeight);
	this->view->setCameraPosition(position);
}

Actor::~Actor()
{
	delete this->view;
}

glm::vec3 Actor::getPosition()
{
	return view->getCameraPosition();
}

btRigidBody* &Actor::getColBody()
{
	return this->body;
}

void Actor::updateColPosition()
{
    btTransform trans;
    body->getMotionState()->getWorldTransform(trans);
    trans.getOrigin();

    this->view->setCameraPosition(glm::vec3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));

	//btScalar matrix[16];
 //   btTransform trans;

 //   body->getMotionState()->getWorldTransform(trans);

 //   if (!body->isStaticObject()) {
 //       // this->mTransform = UtilConversion::btScalar2mat4(matrix);

 //       body->activate();
 //       body->setLinearVelocity(btVector3(direction.x, direction.y, direction.z));
 //   }
}

void Actor::reset()
{
    body->activate();
    body->setLinearVelocity(btVector3(0, 0, 0));
}

void Actor::forward()
{
    body->activate();
    glm::vec3 front = this->view->getFrontVector();
    body->setLinearVelocity(btVector3(front.x, front.y, front.z));
}

void Actor::backward()
{
    body->activate();
    glm::vec3 front = this->view->getFrontVector();
    body->setLinearVelocity(btVector3(-front.x, -front.y, -front.z));
}

void Actor::strafeLeft()
{
    body->activate();
    glm::vec3 right = this->view->getRightVector();
    body->setLinearVelocity(btVector3(-right.x, -right.y, -right.z));
}

void Actor::strafeRight()
{
    body->activate();
    glm::vec3 right = this->view->getRightVector();
    body->setLinearVelocity(btVector3(right.x, right.y, right.z));
}
