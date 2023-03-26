#ifndef DIRECTIONAL_LIGHT_HEADER
#define DIRECTIONAL_LIGHT_HEADER

#include "light.h"
#include "triple.h"
#include <string>

class DirectionalLight : public Light
{
public:
	DirectionalLight(glm::vec3 direction, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), float specular = 0.5f, float ambiant = 0.1f);
	/**
	* DirectionalLight does not have a mesh so this function is empty
	*/
	virtual void setupMesh();
	/**
	* @param shader - The shader used to draw the objects influenced by the light
	* Sets the different properties of the light to the shader
    * The properties are : color; specularStr; ambiantStr; active explained in light.h
	*/
	virtual void setUniforms(Shader& shader);
	static int dirID;

	/**
	* Returns the name of the light, used for Imgui
	*/
	std::string getClassName() override {
		return "Directional light";
	};

	/**
	* Directional Light does not have a positionn, only a direction
	*/
	virtual const bool hasPosition() {
		return false;
	}

	/**
	* @param shader - The shader used to draw the objects influenced by the light
	* Resets the light uniforms in the shader so that it does not affect objects anymore
	*/
	virtual void disableLight(Shader& shader);
	virtual std::vector<Triple<std::string, std::string, float&>> getOptions();

private:
	//directional Light does not have position
	glm::vec3 lightDir;
	float m_specularStr, m_ambiantStr;
	const bool hasAPosition = false;
};

#endif // DIRECTIONAL_LIGHT_HEADER