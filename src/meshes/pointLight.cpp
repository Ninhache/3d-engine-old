#include "../headers/model.h"
#include "../headers/pointLight.h"
#include <glm/gtc/matrix_transform.hpp>

int PointLight::pointID = 0;
PointLight::PointLight(glm::vec3 position, glm::vec3 color, float scale, float specular, float ambiant, float constant, float linear, float quadratic) : Light(position, color){
    this->m_constant = constant;
    this->m_linear = linear;
    this->m_quadratic = quadratic;
    this->m_specularStr = specular;
    this->m_ambiantStr = ambiant;
    this->lightID = PointLight::pointID++;
    this->scale = scale;
    this->setupMesh();
}

void PointLight::setupMesh(){
    
    //Making light extend Model would be too troublesome
    //So using this method instead at the cost of performance
    Model model{ "models/light/sphere.fbx" };
    //The first model is the root node and generaly empty
    Model LightModel = model.getChildren()[0];
    Mesh mesh = LightModel.getMeshes()[0];
    
    std::vector<uint32_t> indices = mesh.getIndices();
    std::vector<Vertex> vertices = mesh.getVertices();

    this->m_indices.insert(this->m_indices.begin(), indices.begin(), indices.end());
    this->m_vertices.insert(this->m_vertices.begin(), vertices.begin(), vertices.end());
    
    this->configureBuffers();
    //working with aiMatrix is tricky, so we might want to change this to glm if it needs to
    this->localTransform = aiMatrix4x4();
}

std::vector<std::pair<std::string, float&>> PointLight::getOptions() {
    static std::vector<std::pair<std::string, float&>> options {
        { "constant", this->m_constant },
        { "linear", this->m_linear },
        { "quadratic", this->m_quadratic },
        { "specular strength", this->m_specularStr },
        { "ambiant strength", this->m_ambiantStr },
    };

    return options;
}

void PointLight::setUniforms(Shader& shader) {
    shader.use();

    std::string currentID = std::to_string(this->lightID);

    std::string lightColor = "pLights[" + currentID + "].lightColor";
    std::string lightPos = "pLights[" + currentID + "].lightPos";

    std::string specularStr = "pLights[" + currentID + "].specularStr";
    std::string ambiantStr = "pLights[" + currentID + "].ambiantStr";
    std::string constant = "pLights[" + currentID + "].constant";
    std::string quadratic = "pLights[" + currentID + "].quadratic";
    std::string linear = "pLights[" + currentID + "].linear";

    std::string active = "pLights[" + currentID + "].active";

    shader.setVec3(lightColor, this->lightColor);
    shader.setVec3(lightPos, this->lightPos);
    
    shader.setFloat(specularStr, this->m_specularStr);
    shader.setFloat(ambiantStr, this->m_ambiantStr);
    shader.setFloat(constant, this->m_constant);
    shader.setFloat(quadratic, this->m_quadratic);
    shader.setFloat(linear, this->m_linear);
    shader.setFloat(active, this->activated);
}