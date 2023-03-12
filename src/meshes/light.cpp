#include "../headers/light.h"


Light::Light(glm::vec3 position, glm::vec3 color){
    this->lightPos = position;
    this->lightColor = color;
}

void Light::draw(Shader& shader, Shader& lightShader) {

    this->setUniforms(shader);
    
    lightShader.use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, this->lightPos);
    model = glm::scale(model, glm::vec3(scale));

    lightShader.setMatrix4("model", model);
    lightShader.setVec3("lightColor", this->lightColor);
    
    glBindVertexArray(this->m_VAO);
    glDrawElements(GL_TRIANGLES, this->m_indices.size(), GL_UNSIGNED_INT, 0);
}

glm::vec3& Light::getPos() {
    return this->lightPos;
}

glm::vec3& Light::getLightColor() {
    return this->lightColor;
}