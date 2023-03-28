
#ifndef MESH_H
#define MESH_H

#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "texture.h"
#include "shader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>          
#include <assimp/postprocess.h>   

/**
* Vertex struct containg the position, normal and coordinates of a vertex
*/
struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textCoord;
};

class Mesh
{
public:
	/**
	* @brief Empty constructor used when loading models
	*/
	Mesh();
	
	/***
	* @param vertices - Vertices of the mesh
	* @param indices - Indices of the mesh
	* @param textures - Textures of the mesh, as of now either of the following type {"diffuseMap","normalMap","specularMap","heightMap","opacityMap"}
	* @param localTransform - This is the localTransform according to its parents, 
	* it needs to be multiplied with the model matrix of the mesh to get it's world transform
	* @param position - Position of the mesh
	*/
	Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices ,std::vector<Texture> textures, aiMatrix4x4 localTransform, glm::vec3 position);
	
	/**
	* @brief Sets the uniforms of the shader (textures, model matrix and normal matrix) and draw the model
	* 
	* @param shader - Shader who will draw the model
	* @param scale - Scale of the model
	*/
	void draw(Shader& shader);
	
	/**
	* @return a vector containing the vertices of the mesh
	*/
	std::vector<Vertex> getVertices();
	
	/**
	* @return a vector containing the indices of the mesh
	*/
	std::vector<uint32_t> getIndices();
	
	/**
	* @return a vector containing the textures of the mesh
	*/
	std::vector<Texture>& getTextures();
	
	/**
	* @brief Sets the new position of the mesh
	* 
	* @param the new position of the mesh
	*/
	void setPosition(glm::vec3 position);

	void setScale(float scale);
protected:
	uint32_t m_VAO, m_VBO, m_EBO;
	std::vector<Vertex> m_vertices;
	std::vector<uint32_t> m_indices;
	std::vector<Texture> m_textures;
	aiMatrix4x4 localTransform;
	glm::vec3 position;
	float scale = 1.0f;
	void configureBuffers();
};

#endif