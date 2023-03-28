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
	/**
	* @brief Construct a new Model object
	*
	* @param position Position of the model
	* @param scale Scale of the model
	* @param flipTextures True if the textures need to be flipped when loaded with stb
	*/
	Model(glm::vec3 position, float scale, bool flipTextures);

	/**
	* @brief Construct a new Model object and calls the loadModel() function
	*
	* @param path Path of the model
	* @param position position of the model, default 0.0
	* @param scale Scale of the model, default 1.0
	* @param flipTextures True if the textures need to be flipped when loaded with stb
	*/
	Model(const std::string& path, glm::vec3 position = glm::vec3(0.0f), float scale = 1.0f, bool flipTextures = true);
	
	/**
	* @brief Loads a model from path using assimp and call the parseNode() function
	* @param Path of the model
	*/
	void loadModel(const std::string& path);
	
	/**
	* @brief parses the nodes created by assimp
	*
	* This is a recursive function, it parses all the nodes in the aiScene wich containes 
	* zero or more Meshes. For each node, it creates and then add it as a child
	* of the specified parent Model
	* 
	*@param node
	*@param scene The aiScene object containing the nodes data
	*@param parent
	*/
	void parseNodes(aiNode* node, const aiScene* scene, Model& parent, aiMatrix4x4& transform);

	/**
	* @brief Creates a Mesh object which is a part of the Model
	* 
	* @param mesh assimp mesh object, used to retrieve informations such as vertices,indices,normals and texture coordinates
	* @param scene used to get materials
	* @param localTransform transformation matrix which is used to get the mesh position relative to parent
	* @return the created mesh
	*/
	Mesh createMesh(aiMesh* mesh, const aiScene* scene, aiMatrix4x4& localTransform);
	
	/**
	* @brief Call each mesh in m_children and each model in m_meshes and call their draw function
	*/
	void draw(Shader& shader);

	/**
	 * @brief Adds a mesh to the model object
	 * 
	 * @param mesh The mesh to be added
	 */
	void addMesh(Mesh mesh);

	/**
	 * @brief Get the Meshes object
	 * 
	 * @return std::vector<Mesh>& 
	 */
	std::vector<Mesh>& getMeshes();

	/**
	 * @brief Get the Children object
	 * 
	 * @return std::vector<Model>& 
	 */
	std::vector<Model>& getChildren();

	/**
	 * @brief Adds specified model as a child of the model calling it
	 * 
	 * @param child The model to be added as child
	 * @return Model& The added model
	 */
	Model& addChild(Model& child);
	
	/**
	 * @brief Set the Scale object
	 * 
	 * In addition of changing the model's scale, it parses all child models
	 * and call their setScale() function with the same value 
	 * 
	 * @param scale 
	*/
	void setScale(float scale);

	/**
	 * @brief Get the Scale object
	 * 
	 * @return float& 
	 */
	float& getScale();
	
	/**
	 * @brief Set the Position object
	 * 
	 * In addition of changing the model's position, it parses all child models
	 * and call their setPosition() function with the same value 
	 * 
	 * @param position 
	 */
	void setPosition(glm::vec3 position);

	/**
	 * @brief Get the Position object
	 * 
	 * @return glm::vec3&
	 */
	glm::vec3& getPosition();
	
	/**
	 * @brief Tells if the model is outlined
	 * 
	 * @return true If the model should be outlined
	 * @return false If the model should not be outlined
	 */
	bool& isOutlined();

	/**
	 * @brief Set the Outlined object
	 * 
	 * @param outline The value to be set
	 */
	void setOutlined(bool outline);

	/**
	 * @brief Tells if the model is active
	 * 
	 * @return true If the model is the model should be drawn
	 * @return false If the model is the model should not be drawn
	 */
	bool& getActive();

	/**
	 * @brief get the directory of the model
	 * 
	 * @return directory - The directory is where the model is located
	 */
	std::string getDirectory();

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