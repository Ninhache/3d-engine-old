#ifndef POINT_LIGHT_HEADER
#define POINT_LIGHT_HEADER
#include "light.h"

class PointLight : public Light
{
public:
	PointLight(glm::vec3 position, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), float constant = 1.0f, float linear = 0.09f, float quadratic = 0.032, float specular = 0.5, float ambiant = 0.1);
	virtual void setupMesh();
	virtual void setUniforms(Shader& shader);
	static int pointID;

private:
	float m_constant, m_linear, m_quadratic;
	float m_specularStr, m_ambiantStr;
};

#endif // POINT_LIGHT_HEADER