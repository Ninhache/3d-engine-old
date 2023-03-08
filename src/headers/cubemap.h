#ifndef CUBEMAP_HEADER_FILE
#define CUBEMAP_HEADER_FILE

#include <iostream>
#include <vector>
#include "texture.h"
#include "mesh.h"

class CubeMap
{

public:
    /* Cubemaps in openGL use a Left handed coordinate system */
	CubeMap(std::string dir, std::vector<std::string> paths);
	CubeMap(std::vector<std::string> paths);
	void configureMesh();
	void configureBuffers();
    void draw(glm::mat4 view, glm::mat4 projection);
private:
	Texture m_texture;
    Shader shader{ "shaders/cubemap.vs","shaders/cubemap.fs" };
	unsigned int m_VAO, m_VBO;
	std::vector<float> m_vertices;
};

#endif // CUBEMAP_HEADER_FILE