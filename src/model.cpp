#include "headers/model.h"
#include "headers/logger.h"


//leave this empty for now
Model::Model() {
}

Model::Model(const std::string& path)
{
	loadModel(path);
}

void Model::loadModel(const std::string& path) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_OptimizeMeshes);
	if (!scene) {
		logger.log(importer.GetErrorString());
		return;
	}

	aiMatrix4x4 mat{};
	parseNodes(scene->mRootNode, scene, *this, mat);
}

/**
* Parses all the nodes in the aiScene wich containes 0 or N Meshes
* it creates a Model for each node and add it as a child of the parent Model
*
*@param node
*@param scene
*@param parent
*/
void Model::parseNodes(aiNode* node, const aiScene* scene, Model& parent, aiMatrix4x4& transform) {
	
	Model model;
	//To calculate the world transform of a mesh, we need to multiply
	//the localTransform of his all parents with its own localTransform matrix.
	aiMatrix4x4 localTransform = transform * node->mTransformation;

	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		unsigned int currentMesh = node->mMeshes[i];
		Mesh mesh = createMesh(scene->mMeshes[currentMesh], scene, localTransform);
		model.addMesh(mesh);
	}

	
	//optimisation is made here to skip a node that contains 0 meshes,
	//but we still want to keep its transformation
	Model& addedModel = node->mNumMeshes > 0 ? parent.addChild(model) : parent;

	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		parseNodes(node->mChildren[i], scene, addedModel, localTransform);
	}
}


Mesh Model::createMesh(aiMesh* mesh, const aiScene* scene, aiMatrix4x4& localTransform) {
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	std::vector<Texture> textures;

	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex{};
		aiVector3D position = mesh->mVertices[i];
		vertex.position = glm::vec3(position.x, position.y, position.z);

		if (mesh->HasNormals()) {
			aiVector3D normal = mesh->mNormals[i];
			vertex.normal = glm::vec3(normal.x, normal.y, normal.z);
		}

		//We only take the first set of textures coordinates since we won't use
		//normal map, specular,... for now
		if (mesh->HasTextureCoords(0)) {
			aiVector3D textCoord = mesh->mTextureCoords[0][i];
			//Only using 2D textures for now
			vertex.textCoord = glm::vec2(textCoord.x, textCoord.y);
		}
		else
			vertex.textCoord = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}

	for (size_t i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (size_t faceIndex = 0; faceIndex < face.mNumIndices; faceIndex++)
		{
			indices.push_back(face.mIndices[faceIndex]);
		}
	}

	return Mesh{ vertices, indices, textures, localTransform };
}

void Model::draw(Shader& shader) {
	//avoiding copying by passing reference
	for (Model& model : this->m_children) {
		model.draw(shader);
	}

	for (Mesh& mesh : this->m_meshes) {
		mesh.draw(shader);
	}
}

Model& Model::addChild(Model& child) {
	this->m_children.push_back(child);
	return this->m_children.back();
}

void Model::addMesh(Mesh mesh) {
	this->m_meshes.push_back(mesh);
}