
#ifndef MESH_H
#define MESH_H

#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "texture.h"
#include "shader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>          
#include <assimp/postprocess.h>   

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textCoord;
};

class Mesh
{
public:
	Mesh();
	Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices ,std::vector<Texture> textures, aiMatrix4x4 localTransform, glm::vec3 position, bool hasTextures);
	void draw(Shader& shader);
	void associateTextures();

protected:
	bool hasTextures = true;
	uint32_t m_VAO, m_VBO, m_EBO;
	std::vector<Vertex> m_vertices;
	std::vector<uint32_t> m_indices;
	std::vector<Texture> m_textures;
	aiMatrix4x4 localTransform;
	glm::vec3 position;
	void configureBuffers();
};

#endif
