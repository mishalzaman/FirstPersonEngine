#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Mesh.h"
#include "Model.h"
#include "Shader.h"
#include "Physics.h"
#include "MeshType.h"
#include "Actor.h"

class Scene
{
	public:
		Scene(int screenWidth, int screenHeight);
		~Scene();
		void update(double dt);
		void render(glm::mat4 projection);
		
		/* Views */
		glm::mat4 viewMat4();
		glm::vec3 viewPosVec3();
		void mousePositionUpdate(double dt, unsigned int x, unsigned int y);

		/* Actor movement */
		void actorForward(double dt);
		void actorBackward(double dt);
		void actorStrafeLeft(double dt);
		void actorStrafeRight(double dt);
	private:
		std::vector<Mesh> staticMeshes;
		Shader shader;
		Physics* physics;
		Actor* actor;
		void loadStaticMeshes();
};

#endif

