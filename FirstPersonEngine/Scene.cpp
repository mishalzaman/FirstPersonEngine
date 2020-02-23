#include "Scene.h"

Scene::Scene(int screenWidth, int screenHeight) :
    shader("shaders/basic_lighting_no_texture.vert", "shaders/basic_lighting_no_texture.frag")
{
    this->physics = new Physics();

    /* STATIC meshes*/
    loadStaticMeshes();
    for (int i = 0; i < this->staticMeshes.size(); i++) {
        this->physics->addStaticBox(this->staticMeshes[i]);
    }

    /* Actor setup */
    Model model = Model("assets/map1/player.dae");
    this->actor = new Actor(screenWidth, screenHeight, model.meshes[0].position);
    this->physics->addKinematicShape(this->actor->getPosition(), this->actor->getColBody());
}

Scene::~Scene()
{
     delete this->physics;
     delete this->actor;
}

void Scene::update(double dt)
{
    this->physics->simulate(dt);
    this->actor->updateColPosition();
    this->actor->reset();
}

void Scene::render(glm::mat4 projection)
{
    // this->physics->drawDebugData(projection, this->viewMat4());

    this->shader.use();
    this->shader.setMat4("projection", projection);
    this->shader.setMat4("view", this->viewMat4());
    this->shader.setFloat("shininess", 32.0f);
    this->shader.setVec3("material_specular", glm::vec3(0.1f, 0.1f, 0.1f));
    this->shader.setVec3("light_specular", glm::vec3(0.5f, 0.5f, 0.5f));
    this->shader.setVec3("lightPos", glm::vec3(0,10,0));
    this->shader.setVec3("viewPos", this->viewPosVec3());

    /* static meshes */
	for (int i = 0; i < this->staticMeshes.size(); i++) {
        this->shader.setMat4("model", this->staticMeshes[i].mTransform);

        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr = 1;
        unsigned int heightNr = 1;
        for (unsigned int j = 0; j < this->staticMeshes[i].textures.size(); j++)
        {
            glActiveTexture(GL_TEXTURE0 + j); // active proper texture unit before binding
            // retrieve texture number (the N in diffuse_textureN)
            std::string number;
            std::string name = this->staticMeshes[i].textures[j].type;
            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
                number = std::to_string(specularNr++); // transfer unsigned int to stream
            else if (name == "texture_normal")
                number = std::to_string(normalNr++); // transfer unsigned int to stream
            else if (name == "texture_height")
                number = std::to_string(heightNr++); // transfer unsigned int to stream

            // now set the sampler to the correct texture unit
            glUniform1i(glGetUniformLocation(this->shader.ID, (name + number).c_str()), j);
            // and finally bind the texture
            glBindTexture(GL_TEXTURE_2D, this->staticMeshes[i].textures[j].id);
        }

        // draw mesh
        glBindVertexArray(this->staticMeshes[i].VAO);
        glDrawElements(GL_TRIANGLES, this->staticMeshes[i].indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // always good practice to set everything back to defaults once configured.
        glActiveTexture(GL_TEXTURE0);
	}
}

glm::mat4 Scene::viewMat4()
{
    return this->actor->view->getViewMatrix();
}

glm::vec3 Scene::viewPosVec3()
{
    return this->actor->view->getCameraPosition();
}

void Scene::mousePositionUpdate(double dt, unsigned int x, unsigned int y)
{
    this->actor->view->mousePositionUpdate(dt, x, y);
}

void Scene::actorForward(double dt)
{
    this->actor->forward();
}

void Scene::actorBackward(double dt)
{
    this->actor->backward();
}

void Scene::actorStrafeLeft(double dt)
{
    this->actor->strafeLeft();
}

void Scene::actorStrafeRight(double dt)
{
    this->actor->strafeRight();
}

void Scene::loadStaticMeshes()
{
    Model* model = new Model("assets/map1/map1.dae");
    this->staticMeshes = model->meshes;

    delete model;
}
