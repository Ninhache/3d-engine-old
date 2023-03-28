#ifndef LIGHT_CLASS_HEADER
#define LIGHT_CLASS_HEADER

#include "mesh.h"
#include "triple.h"

#include <string>

/**
 * @brief The light class, all different types of lights will extend this one 
 * 
 *@par Specular
 * Specular lightning adds bright spots to a reflective or glossy surface, it helps in identifying its shape
 * and its position relative to the light
 *
 *@par Ambiant
 * Ambiant lightning is a constant and fixed light source
 * that affect all objects in the scene, it is sometimes used to simulate natural light
 * or pre-existing ones
 * 
 */
class Light : public Mesh
{
public:
	/**
	 * @brief Construct a new Light object
	 *
	 * @param position - The position of the light
	 * @param color - Color of the light, default is white
	 * @param activated - Tells if the light should be drawn or not (and affect other objects)
	 */
	Light(glm::vec3 position = glm::vec3(1.8f, 0.2f, 0.3f), glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), bool activated = true);

	/**
	 * @param shader - The shader used to draw the objects influenced by the light
	 * @param lightShader - The shader used to draw the actual light
	 */
	void draw(Shader &shader, Shader &lightShader);

	/**
	 * @brief Get the reference to the position of the light
	 *
	 * @return glm::vec3&
	 */
	glm::vec3 &getPosition();

	/**
	 * @brief Get the reference to the color of the light
	 *
	 * @return glm::vec3&
	 */
	glm::vec3 &getColor();

	/**
	 * @brief Get the reference to the boolean indicating if the light is active or not
	 *
	 * @return true If the light should be drawn
	 * @return false If the light should not be drawn
	 */
	bool &getActive();

	/**
	 * @brief Pure virtual method destined to be overriden by children classes
	 * Sets up the mesh of the light by filling it's vertices and/or indices vector(s)
	 */
	virtual void setupMesh() = 0;

	/**
	 * @brief Pure virtual method destined to be overriden by children classes
	 *
	 * @param shader - The shader used to draw the objects influenced by the light
	 * Sets the uniforms of the shader according to light's properties
	 */
	virtual void setUniforms(Shader &shader) = 0;

	/**
	 * @brief Get the name of the class
	 *
	 * @return std::string
	 */
	virtual std::string getClassName()
	{
		return "Light";
	}

	/**
	 * @brief Pure virtual method destined to be overriden by children classes
	 *
	 * @param shader - The shader used to draw the objects influenced by the light
	 * Resets the light uniforms in the shader so that it does not affect objects anymore
	 */
	virtual void disableLight(Shader &shader) = 0;

	/**
	 * @brief Pure virtual method destined to be overriden by children classes
	 * tells if the light has a position or not
	 *
	 * @return true If the light has a position
	 * @return false If the light does not have a position (ex: Directional Light)
	 */
	virtual const bool hasPosition() = 0;

	/**
	 * @brief Get the Options of the Light
	 *
	 * @return std::vector<Triple<std::string, std::string, float&>>
	 */
	virtual std::vector<Triple<std::string, std::string, float &>> getOptions() = 0;
	// ID if the light
	int lightID;

protected:
	// Default position
	glm::vec3 position;
	// Default light color
	glm::vec3 color;
	// Scale of the light
	float scale;
	// True the light is activated (drawn)
	bool activated = false;
};

#endif // LIGHT_CLASS_HEADER