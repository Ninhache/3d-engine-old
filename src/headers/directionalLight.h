#ifndef DIRECTIONAL_LIGHT_HEADER
#define DIRECTIONAL_LIGHT_HEADER

#include "light.h"

#include <string>

class DirectionalLight : public Light
{
public:
	DirectionalLight(glm::vec3 direction, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), float specular = 0.5f, float ambiant = 0.1f);
	virtual void setupMesh();
	virtual void setUniforms(Shader& shader);
	static int dirID;

	std::string getClassName() override {
		return "Directional light";
	};

	virtual std::vector<std::pair<std::string, float&>> getOptions();

private:
	//directional Light does not have position
	glm::vec3 lightDir;
	float m_specularStr, m_ambiantStr;
};

#endif // DIRECTIONAL_LIGHT_HEADER