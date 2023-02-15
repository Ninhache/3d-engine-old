#include "../headers/pointLight.h"
#include <glm/gtc/matrix_transform.hpp>

PointLight::PointLight(glm::vec3 position, glm::vec3 color, float constant, float linear, float quadratic, float specular, float ambiant) : Light(position, color){
    this->m_constant = constant;
    this->m_linear = linear;
    this->m_quadratic = quadratic;
    this->m_specularStr = specular;
    this->m_ambiantStr = ambiant;
    this->setupMesh();
}

void PointLight::setupMesh(){

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

void PointLight::setUniforms(Shader& shader) {
    shader.use();
    shader.setVec3("pLight.lightPos", this->lightPos);
    shader.setFloat("pLight.specularStr", this->m_specularStr);
    shader.setFloat("pLight.ambiantStr", this->m_ambiantStr);
    shader.setVec3("pLight.lightColor", this->lightColor);
    shader.setFloat("pLight.constant", this->m_constant);
    shader.setFloat("pLight.linear", this->m_linear);
    shader.setFloat("pLight.quadratic", this->m_quadratic);
}