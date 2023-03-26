#ifndef LIGHT_CLASS_HEADER
#define LIGHT_CLASS_HEADER

#include "mesh.h"
#include "triple.h"

#include <string>

class Light : public Mesh
{
public:
	/**
	* @param position - The position of the light
	* @param color - Color of the light, default is white
	* @param activated - Tells if the light should be drawn or not (and affect other objects) 
	*/
	Light(glm::vec3 position, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), bool activated = true);
	/**
	* @param shader - The shader used to draw the objects influenced by the light
	* @param lightShader - The shader used to draw the actual light
	*/
	void draw(Shader& shader, Shader& lightShader);
	/**
	* @return the reference to the position of the light
	*/
	glm::vec3& getPosition();
	/**
	* @return the reference to the color of the light
	*/
	glm::vec3& getColor();
	/**
	* @return the reference to the boolean indicating if the light is active or not
	*/
	bool& getActive();
	/**
	* Pure virtual method destined to be overriden by children classes
	* Sets up the mesh of the light by filling it's vertices and/or indices vector(s)
	*/
	virtual void setupMesh() = 0;
	/**
	* Pure virtual method destined to be overriden by children classes
	* @param shader - The shader used to draw the objects influenced by the light
	* Sets the uniforms of the shader according to light's properties
	*/
	virtual void setUniforms(Shader& shader) = 0;

	/**
	* @return the name of the light, used for Imgui
	*/
	virtual std::string getClassName() {
		return "Light";
	}

	/**
	* Pure virtual method destined to be overriden by children classes
	* @param shader - The shader used to draw the objects influenced by the light
	* Resets the light uniforms in the shader so that it does not affect objects anymore
	*/
	virtual void disableLight(Shader& shader) = 0;
	/**
	* Pure virtual method destined to be overriden by children classes
	* tells if the light has a position or not
	*/
	virtual const bool hasPosition() = 0;
	virtual std::vector<Triple<std::string, std::string, float&>> getOptions() = 0;
	//ID if the light
	int lightID;

protected:
	//Default light position
	glm::vec3 position = glm::vec3(1.8f, 0.2f, 0.3f);
	//Default light color
	glm::vec3 color;
	//Scale of the light
	float scale;
	//True the light is activated (drawn)
	bool activated = false;
};

#endif // LIGHT_CLASS_HEADER