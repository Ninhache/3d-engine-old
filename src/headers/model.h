#ifndef OBJECT_MODEL_H
#define OBJECT_MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>          
#include <assimp/postprocess.h>

#include "mesh.h"
#include "vector"
#include "iostream"

class Model
{
public:
	/* 
	* @param position - Position of the model
	* @param scale - Scale of the model
	* @param flipTextures - True if the textures need to be flipped when loaded with stb
	*/
	Model(glm::vec3 position, float scale, bool flipTextures);
	/*
	* @param path - Path of the model
	* @param position - position of the model, default 0.0
	* @param scale - Scale of the model, default 1.0
	* @param flipTextures - True if the textures need to be flipped when loaded with stb
	*/
	Model(const std::string& path, glm::vec3 position = glm::vec3(0.0f), float scale = 1.0f, bool flipTextures = true);
	
	/**
	*Load a model from path using assimp
	* @path - Path of the model
	*/
	void loadModel(const std::string& path);
	
	/**
	* Parses all the nodes in the aiScene wich containes 0 or N Meshes
	* it creates a Model for each node and add it as a child of the parent Model
	*@param node
	*@param scene
	*@param parent
	*/
	void parseNodes(aiNode* node, const aiScene* scene, Model& parent, aiMatrix4x4& transform);

	/**
	* Creates a Mesh object which is a part of the Model
	* @param mesh - assimp mesh object, used to retrieve informations such as vertices,indices,normals and texture coordinates
	* @param scene - used to get materials
	* @param localTransform - transformation matrix which is used to get the mesh position relative to parent
	* @return the created mesh
	*/
	Mesh createMesh(aiMesh* mesh, const aiScene* scene, aiMatrix4x4& localTransform);
	
	/**
	*Call each mesh in m_children and each model in m_meshes and call their draw function
	*/
	void draw(Shader& shader);
	void addMesh(Mesh mesh);
	std::vector<Mesh>& getMeshes();
	std::vector<Model>& getChildren();
	Model& addChild(Model& child);
	
	void setScale(float scale);
	float& getScale();
	
	void setPosition(glm::vec3 position);
	glm::vec3& getPosition();
	
	bool& isOutlined();
	void setOutlined(bool outline);
	bool& getActive() {
		return this->activated;
	}

private:
	std::string m_directory;
	std::vector<Mesh> m_meshes;
	std::vector<Model> m_children;
	std::vector<Texture> loadMaterial(aiMaterial* material, aiTextureType type);
	glm::vec3 position;
	float scale;
	bool outlined = false;
	//User must indicate wether or not a texture should be flipped
	bool flipTextures;
	bool activated = false;
};

#endif // OBJECT_MODEL_H