#include "headers/Mesh.h"

std::vector<float> vertices, indices, normals;
uint32_t VAO, VBO, VEO;
std::vector<Texture> textures;
std::vector<Mesh> children;

Mesh::Mesh(std::vector<float> vertices, std::vector<float> indices, std::vector<float> normals, std::vector<Texture> textures) {
	this->vertices = vertices;
	this->indices = indices;
	this->normals = normals;
	this->textures = textures;
}

void Mesh::configureBuffers() {

}
void Mesh::draw(const Shader& shader) {

}
void Mesh::associateTextures() {

}
