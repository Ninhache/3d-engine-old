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
	Model();
	Model(const std::string& path);
	
	/**
	*Load a model from path using assimp
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
	* @param mesh - assimp mesh object, used to retrieve informations such as vertices,indices,normals and texture coordinates
	* @param scene - used to get materials
	* @param localTransform - transformation matrix which is used to get the mesh position relative to parent
	*@return the created mesh
	*/
	Mesh createMesh(aiMesh* mesh, const aiScene* scene, aiMatrix4x4& localTransform);
	
	/**
	*Call each mesh in m_children and each model in m_meshes and call their draw function
	*/
	void draw(Shader& shader);
	void addMesh(Mesh mesh);
	Model& addChild(Model& child);

private:
	std::string m_directory;
	std::vector<Mesh> m_meshes;
	std::vector<Model> m_children;
	std::vector<Texture> loadMaterial(aiMaterial* material, aiTextureType type);
};

#endif // !OBJECT_MODEL_H
