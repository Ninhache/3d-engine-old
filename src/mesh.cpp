#include "headers/mesh.h"

// ????
// std::vector<float> vertices, indices, normals;
// uint32_t VAO, VBO, VEO;
// std::vector<Texture> textures;
// std::vector<Mesh> children;

/**
 * @brief Construct a new Mesh:: Mesh object
 * 
 * @param vertices 
 * @param indices 
 * @param normals 
 * @param textures 
 */
Mesh::Mesh(std::vector<float> vertices, std::vector<float> indices, std::vector<float> normals, std::vector<Texture> textures) {
	this->m_vertices = vertices;
	this->m_indices = indices;
	this->m_normals = normals;
	this->m_textures = textures;
}

void Mesh::configureBuffers() {

}

void Mesh::draw(const Shader& shader) {

}

void Mesh::associateTextures() {

}
