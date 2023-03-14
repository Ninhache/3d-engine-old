#ifndef POINT_LIGHT_HEADER
#define POINT_LIGHT_HEADER

#include "light.h"
#include "triple.h"
#include <string>

class PointLight : public Light
{
public:
	PointLight(glm::vec3 position, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), float scale = 1.0f, float specular = 0.5, float ambiant = 0.1, float constant = 1.0f, float linear = 0.09f, float quadratic = 0.032);
	virtual void setupMesh();
	virtual void setUniforms(Shader& shader);
	void setScale(float scale);
	static int pointID;

	std::string getClassName() override {
		return "Point light";
	};

	virtual const bool hasPosition() {
		return true;
	}

	virtual std::vector<Triple<std::string, std::string, float&>> getOptions();

private:
	float m_constant, m_linear, m_quadratic;
	float m_specularStr, m_ambiantStr;
	const bool hasAPosition = true;
};

#endif // POINT_LIGHT_HEADER