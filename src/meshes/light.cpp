#include "../headers/light.h"

Light::Light() {
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
    this->localTransform = aiMatrix4x4();
}