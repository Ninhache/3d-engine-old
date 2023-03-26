#include "../headers/light.h"


Light::Light(glm::vec3 position, glm::vec3 color, bool activated){
    this->position = position;
    this->color = color;
    this->activated = activated;
}

void Light::draw(Shader& shader, Shader& lightShader) {

    this->setUniforms(shader);
    
    lightShader.use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, this->position);
    model = glm::scale(model, glm::vec3(scale));

    lightShader.setMatrix4("model", model);
    lightShader.setVec3("lightColor", this->color);
    
    glBindVertexArray(this->m_VAO);
    glDrawElements(GL_TRIANGLES, this->m_indices.size(), GL_UNSIGNED_INT, 0);
}

glm::vec3& Light::getPosition() {
    return this->position;
}

glm::vec3& Light::getColor() {
    return this->color;
}

bool& Light::getActive() {
    return this->activated;
}