#pragma once
#include "mesh.h"

class Light : public Mesh
{
public:
	Light();
	Light(glm::vec3 position, glm::vec3 color = glm::vec3(1.0f,1.0f,1.0f));
	void draw(Shader& shader);
	glm::vec3 getPos();
	glm::vec3 getLightColor();
private:
	//Default light position
	glm::vec3 lightPos = glm::vec3(1.8f, 0.2f, 0.3f);
	glm::vec3 lightColor = glm::vec3(0.0f, 0.678f, 0.827f);
};