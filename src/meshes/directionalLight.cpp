#include "../headers/directionalLight.h"
#include <glm/gtc/matrix_transform.hpp>

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 color, float specular, float ambiant) : Light(color) {
    this->m_specularStr = specular;
    this->m_ambiantStr = ambiant;
    this->lightDir = direction;
    this->setupMesh();
}

void DirectionalLight::setupMesh() {
    //Directional light does not have a mesh
}

void DirectionalLight::setUniforms(Shader& shader) {
    shader.use();
    shader.setVec3("dLight.lightDir", this->lightDir);
    shader.setFloat("dLight.specularStr", this->m_specularStr);
    shader.setFloat("dLight.ambiantStr", this->m_ambiantStr);
    shader.setVec3("dLight.lightColor", this->lightColor);
}