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
	CubeMap(std::vector<std::string> paths);
	CubeMap(std::string dir, std::vector<std::string> paths);
	CubeMap(){
		this->configureMesh();
	}
	void configureMesh();
	void configureBuffers();
    void draw(glm::mat4 view, glm::mat4 projection);
protected:
	Texture m_texture;
    std::unique_ptr<Shader> shader;
	std::vector<float> m_vertices;
private:
	unsigned int m_VAO, m_VBO;
};

#endif // CUBEMAP_MOCK_HEADER_FILE