#include "../headers/light.h"

Light::Light() : Mesh() {
	this->m_indices = {
        //Top
        2, 6, 7, 2, 3, 7,
        //Bottom
        0, 4, 5, 0, 1, 5,
        //Left
        0, 2, 6, 0, 4, 6,
        //Right
        1, 3, 7, 1, 5, 7,
        //Front
        0, 2, 3, 0, 1, 3,
        //Back
        4, 6, 7, 4, 5, 7
    };
    this->m_vertices = {
        Vertex{glm::vec3(-1, -1,  0.5),glm::vec3(0.0f,0.0f,0.0f)}, //0
        Vertex{glm::vec3(1, -1,  0.5),glm::vec3(0.0f,0.0f,0.0f)}, //0
        Vertex{glm::vec3(-1,  1,  0.5),glm::vec3(0.0f,0.0f,0.0f)}, //0
        Vertex{glm::vec3(1,  1,  0.5),glm::vec3(0.0f,0.0f,0.0f)}, //0
        Vertex{glm::vec3(-1, -1, -0.5),glm::vec3(0.0f,0.0f,0.0f)}, //0
        Vertex{glm::vec3(1, -1, -0.5),glm::vec3(0.0f,0.0f,0.0f)}, //0
        Vertex{glm::vec3(-1,  1, -0.5),glm::vec3(0.0f,0.0f,0.0f)}, //0
        Vertex{glm::vec3(1,  1, -0.5),glm::vec3(0.0f,0.0f,0.0f)}, //0
    };

    this->configureBuffers();
    //working with aiMatrix is tricky, so we might want to change this to glm if it needs to
    this->localTransform = aiMatrix4x4();
}

Light::Light(glm::vec3 position, glm::vec3 color) : Light() {
    this->lightColor = color;
}

void Light::draw(Shader& shader) {

    shader.use();
    //We set the correct model for the Mesh (this is the localTransform according to its parents, so its world transform)
    glm::mat4 model = glm::transpose(glm::make_mat4(&this->localTransform.a1));
    model = glm::translate(model, this->lightPos);
    model = glm::scale(model, glm::vec3(0.4f));
    shader.setMatrix4("model", model);
    shader.setVec3("lightColor", this->lightColor);

    glBindVertexArray(this->m_VAO);
    glDrawElements(GL_TRIANGLES, this->m_indices.size(), GL_UNSIGNED_INT, 0);
}

glm::vec3 Light::getPos() {
    return this->lightPos;
}

glm::vec3 Light::getLightColor() {
    return this->lightColor;
}