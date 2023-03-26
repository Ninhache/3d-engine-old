#ifndef DIRECTIONAL_LIGHT_HEADER
#define DIRECTIONAL_LIGHT_HEADER

#include "light.h"
#include "triple.h"
#include <string>

class DirectionalLight : public Light
{
public:
	/**
	 * @brief Construct a new DirectionalLight object
	 *
	 * @param direction - The direction vector of the light
	 * @param color - Color of the light, default is white
	 * @param specular - specular strength of the light
	 * @param ambiant - ambiant strenght of the light
	 */
	DirectionalLight(glm::vec3 direction, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), float specular = 0.5f, float ambiant = 0.1f);

	/**
	 * @brief Sets up the vertices and indices for the light object
	 *
	 * DirectionalLight does not have a mesh so this function is empty
	 *
	 */
	virtual void setupMesh();

	/**
	 * @brief Sets the different properties of the light to the shader
	 * The properties are : color; specularStr; ambiantStr; active explained in light.h
	 *
	 * @param shader - The shader used to draw the objects influenced by the light
	 */
	virtual void setUniforms(Shader &shader);

	/**
	 * @brief Get the name of the class
	 *
	 * @return std::string
	 */
	std::string getClassName() override
	{
		return "Directional light";
	};

	/**
	 * @brief Tells if the light has a position
	 *
	 * Directional Light does not have a position, only a direction
	 *
	 * @return true If the light has a position
	 * @return false If the light does not have a position (ex: Directional Light)
	 */
	const bool hasPosition()
	{
		return false;
	}

	/**
	 * @brief Resets the light uniforms in the shader
	 * so that it does not affect objects anymore
	 *
	 * @param shader - The shader used to draw the objects influenced by the light
	 */
	virtual void disableLight(Shader &shader);

	/**
	 * @brief Get the Options for the light
	 *
	 * @return std::vector<Triple<std::string, std::string, float&>>
	 */
	virtual std::vector<Triple<std::string, std::string, float &>> getOptions();
	static int dirID;

private:
	// directional Light does not have position
	glm::vec3 lightDir;
	float m_specularStr, m_ambiantStr;
	const bool hasAPosition = false;
};

#endif // DIRECTIONAL_LIGHT_HEADER