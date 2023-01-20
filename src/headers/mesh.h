
#ifndef MESH_H
#define MESH_H

#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "texture.h"
#include "shader.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textCoord;
};

class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices ,std::vector<Texture> textures);
	void draw(Shader shader);
	void associateTextures();
	void addChild(Mesh mesh);

private:
	void configureBuffers();
	std::vector<Vertex> m_vertices;
	std::vector<uint32_t> m_indices;
	std::vector<Texture> m_textures;
	uint32_t m_VAO, m_VBO, m_VEO;
	std::vector<Mesh> m_children;
};

#endif
