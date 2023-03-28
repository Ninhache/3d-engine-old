#ifndef CUBEMAP_HEADER_FILE
#define CUBEMAP_HEADER_FILE

#include <iostream>
#include <vector>
#include <memory>

#include "texture.h"
#include "mesh.h"

class CubeMap
{

public:
	/* Cubemaps in openGL use a Left handed coordinate system */

	/**
	 * @brief Creates a new CubeMap,
	 * paths should look something like {"path/to/folder/posx.*"}
	 * for all values : "posx.jpg","negx.jpg","posy.jpg","negy.jpg","posz.jpg","negz.jpg" representing the faces of the cubemap
	 *
	 * @param paths - All path for the cubemap textures
	 */
	CubeMap(std::vector<std::string> paths);

	/**
	 * @brief Creates a new CubeMap and concatenate all paths values with dir
	 *
	 * @param dir - The directory where the textures are located
	 * @param paths - All file names for the textures,
	 * paths should look something like {"posx.*", "posy.*"} with dir being "path/to/folder/"
	 * for all values : "posx.jpg","negx.jpg","posy.jpg","negy.jpg","posz.jpg","negz.jpg" representing the faces of the cubemap
	 */
	CubeMap(std::string dir, std::vector<std::string> paths);

	/**
	 * @brief Used for tests
	 */
	CubeMap()
	{
		this->configureMesh();
	}

	/**
	 * @brief sets m_vertices to make up a cube
	 */
	void configureMesh();

	/**
	 * @brief sets up VAO and VBO for the cube
	 */
	void configureBuffers();

	/**
	 * @brief Draw the cubemap (or skybox) to the screen
	 *
	 * @param view - The view matrix
	 * @param projection - The projection matrix
	 */
	void draw(glm::mat4 view, glm::mat4 projection);

protected:
	// Texture of the cubemap containing all textures
	Texture m_texture;
	// The shader used to draw the cubemap
	std::unique_ptr<Shader> shader;
	// Cube vertices
	std::vector<float> m_vertices;

private:
	unsigned int m_VAO, m_VBO;
};

#endif // CUBEMAP_MOCK_HEADER_FILE