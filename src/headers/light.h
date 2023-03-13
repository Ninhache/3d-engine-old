#ifndef LIGHT_CLASS_HEADER
#define LIGHT_CLASS_HEADER

#include "mesh.h"

#include <string>

class Light : public Mesh
{
public:
	Light(glm::vec3 position, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), bool activated = true);
	void draw(Shader& shader, Shader& lightShader);
	glm::vec3& getPos();
	glm::vec3& getLightColor();
	int lightID;

	void setActive(bool active);
	virtual void setupMesh() = 0;
	virtual void setUniforms(Shader& shader) = 0;
	virtual std::string getClassName() {
		return "Light";
	}
	virtual std::vector<std::pair<std::string, float&>> getOptions() = 0;

protected:
	//Default light position
	glm::vec3 lightPos = glm::vec3(1.8f, 0.2f, 0.3f);
	glm::vec3 lightColor = glm::vec3(0.0f, 0.678f, 0.827f);
	float scale;
	bool activated = false;
};

#endif // LIGHT_CLASS_HEADER