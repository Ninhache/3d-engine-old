#ifndef LIGHT_CLASS_HEADER
#define LIGHT_CLASS_HEADER

#include "mesh.h"
#include "triple.h"

#include <string>

class Light : public Mesh
{
public:
	Light(glm::vec3 position, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), bool activated = true);
	void draw(Shader& shader, Shader& lightShader);
	glm::vec3& getPosition();
	glm::vec3& getColor();
	int lightID;

	bool& getActive() {
		return this->activated;
	}
	
	virtual void setupMesh() = 0;
	virtual void setUniforms(Shader& shader) = 0;

	virtual std::string getClassName() {
		return "Light";
	}

	virtual void disableLight(Shader& shader) = 0;
	virtual const bool hasPosition() = 0;
	virtual std::vector<Triple<std::string, std::string, float&>> getOptions() = 0;

protected:
	//Default light position
	glm::vec3 position = glm::vec3(1.8f, 0.2f, 0.3f);
	glm::vec3 color = glm::vec3(0.0f, 0.678f, 0.827f);
	float scale;
	bool activated = false;
};

#endif // LIGHT_CLASS_HEADER