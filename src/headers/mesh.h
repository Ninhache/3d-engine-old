#ifndef MESH_H
#define MESH_H

#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "texture.h"
#include "shader.h"
#include <glm/vector_relational.hpp>

class Mesh
{
public:
	Mesh(std::vector<float>, std::vector<float>, std::vector<float>, std::vector<Texture>);
	// ~Mesh();
	
	void draw(const Shader&);
	void configureBuffers();
	void associateTextures();

private:
	std::vector<float> m_vertices, m_indices, m_normals;
	std::vector<Texture> m_textures;
	uint32_t m_VAO, m_VBO, m_VEO;
	std::vector<Mesh> m_children;
};

#endif