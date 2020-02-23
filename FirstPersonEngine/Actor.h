#ifndef ACTOR_H
#define ACTOR_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <bullet/btBulletCollisionCommon.h>
#include <bullet/btBulletDynamicsCommon.h>

#include "CameraFP.h"

class Actor
{
	public:
		Actor(int &screenWidth, int &screenHeight, glm::vec3 position);
		~Actor();
		CameraFP* view;
		glm::vec3 getPosition();
		btRigidBody* &getColBody();
		void updateColPosition();

		/* movement */
		void reset();
		void forward();
		void backward();
		void strafeLeft();
		void strafeRight();
	private:
		btRigidBody* body;
};

#endif

