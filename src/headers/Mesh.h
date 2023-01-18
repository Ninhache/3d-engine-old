#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Texture.h"
#include "shader.h"

class Mesh
{
public:
	Mesh(std::vector<float> vertices, std::vector<float> indices, std::vector<float> normals, std::vector<Texture> textures);
	void draw(const Shader& shader);
	void configureBuffers();
	void associateTextures();
	~Mesh();

private:
	std::vector<float> vetices, indices, normals;
	std::vector<Texture> textures;
	uint32_t VAO, VBO, VEO;
	std::vector<Mesh> children;
};

