#include "../headers/directionalLight.h"
#include <glm/gtc/matrix_transform.hpp>

int DirectionalLight::dirID = 0;

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 color, float specular, float ambiant) : Light(color) {
    this->m_specularStr = specular;
    this->m_ambiantStr = ambiant;
    this->lightDir = direction;
    this->lightID = DirectionalLight::dirID++;
    this->setupMesh();
}

void DirectionalLight::setupMesh() {
    //Directional light does not have a mesh
}

std::vector<std::pair<std::string, float&>> DirectionalLight::getOptions() {
    
    static std::vector<std::pair<std::string, float&>> options {
        { "specular strength", this->m_specularStr },
        { "ambiant strength", this->m_ambiantStr },
    };

    return options;
}

void DirectionalLight::setUniforms(Shader& shader) {
    shader.use();

    std::string currentID = std::to_string(this->lightID);
    
    std::string lightDir = "dLight[" + currentID + "].lightDir";
    std::string lightColor = "dLight[" + currentID + "].lightColor";

    std::string specularStr = "dLight[" + currentID + "].specularStr";
    std::string ambiantStr = "dLight[" + currentID + "].ambiantStr";

    std::string active = "dLight[" + currentID + "].active";
    
    shader.setVec3(lightColor, this->lightColor);
    shader.setVec3(lightDir, this->lightDir);

    shader.setFloat(specularStr, this->m_specularStr);
    shader.setFloat(ambiantStr, this->m_ambiantStr);
    shader.setFloat(active, this->activated);
}