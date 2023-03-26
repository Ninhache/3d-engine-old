#ifndef POINT_LIGHT_HEADER
#define POINT_LIGHT_HEADER

#include "light.h"
#include "triple.h"
#include <string>

class PointLight : public Light
{
public:
	/**
	 * @brief Construct a new Point Light object
	 *
	 * @see Light header for detailed description of the ambiant and specular
	 *
	 * @param position The position of the light in the scene
	 * @param color The color of the light
	 * @param scale The scale factor of the light
	 * @param specular The specular strength of the light
	 * @param ambiant The ambiant strength of the light
	 * @param constant The constant used in light calculations, should stay 1.0
	 * @param linear Reduces the intensity of the light linearly over distance
	 * @param quadratic Reduces the intensity of the light quadratically over distance
	 */
	PointLight(glm::vec3 position, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), float scale = 1.0f, float specular = 0.5, float ambiant = 0.1, float constant = 1.0f, float linear = 0.09f, float quadratic = 0.032);

	/**
	 * @brief Sets up the vertices and indices for the light object
	 *
	 * Creates a sphere Model retrieve is vertices and indices
	 *
	 */
	virtual void setupMesh();

	/**
	 * @brief Sets the uniforms of the shader given in parameter
	 * with the values needed for light calulations
	 *
	 * @param shader The shader used for light calculations
	 */
	virtual void setUniforms(Shader &shader);

	/**
	 * @brief Sets the Scale of the light
	 *
	 * @param scale
	 */
	void setScale(float scale);
	static int pointID;

	/**
	 * @brief Get the name of the class
	 *
	 * @return std::string
	 */
	std::string getClassName() override
	{
		return "Point light";
	};

	/**
	 * @brief Tells if the light has a position
	 *
	 * @return true If the light has a position
	 * @return false If the light does not have a position (ex: Directional Light)
	 */
	const bool hasPosition()
	{
		return true;
	}

	/**
	 * @brief Resets the light uniforms in the shader
	 * so that it does not affect objects anymore
	 *
	 * @param shader - The shader used to draw the objects influenced by the light
	 */
	void disableLight(Shader &shader);

	/**
	 * @brief Get the Options for the light
	 *
	 * @return std::vector<Triple<std::string, std::string, float&>>
	 */
	std::vector<Triple<std::string, std::string, float &>> getOptions();

private:
	float m_constant, m_linear, m_quadratic;
	float m_specularStr, m_ambiantStr;
	const bool hasAPosition = true;
};

#endif // POINT_LIGHT_HEADER