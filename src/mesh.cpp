#include "headers/mesh.h"

Mesh::Mesh() {}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Texture> textures, aiMatrix4x4 localTransform, glm::vec3 position) {
	this->m_vertices = vertices;
	this->m_indices = indices;
	this->m_textures = textures;
	this->localTransform = localTransform;
	this->position = position;
	configureBuffers();
}


void Mesh::configureBuffers() {

	glGenVertexArrays(1, &this->m_VAO);
	glGenBuffers(1, &this->m_VBO);
	glGenBuffers(1, &this->m_EBO);

	glBindVertexArray(this->m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*m_vertices.size(), &this->m_vertices[0], GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * m_indices.size(), &this->m_indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,textCoord));


	glBindVertexArray(0);

}
void Mesh::draw(Shader& shader) {
	int diffuseCpt = 0, normalCpt = 0, specularCpt=0, heightCpt = 0, opacityCpt = 0;
	int counter = 0;
	std::string samplerName;

	for (size_t i = 0; i < this->m_textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		switch (this->m_textures[i].getType()) { 
			case aiTextureType_DIFFUSE:
				samplerName = "diffuseMap";
				counter = diffuseCpt++;
				break;
			case aiTextureType_NORMALS:
				samplerName = "normalMap";
				counter = normalCpt++;
				break;
			case aiTextureType_SPECULAR:
				samplerName = "specularMap";
				counter = specularCpt++;
				break;
			case aiTextureType_HEIGHT:
				samplerName = "heightMap";
				counter = heightCpt++;
				break;
			case aiTextureType_OPACITY:
				samplerName = "opacityMap";
				counter = opacityCpt++;
				break;
			default:
				counter = -1;
				samplerName = "";
		}

		int location = glGetUniformLocation(shader.getId(), (samplerName + std::to_string(counter)).c_str());
		if (location >= 0) {
			glUniform1i(location, i);
			glBindTexture(GL_TEXTURE_2D, this->m_textures[i].getID());
		}
	}
			
	shader.use();
	//We set the correct model for the Mesh (this is the localTransform according to its parents, so its world transform)
	glm::mat4 model = glm::transpose(glm::make_mat4(&this->localTransform.a1));
	
	//scaling the model down (primarily useful for fbx models)
	//Models with an x of 1 are usually of good size so we scale by that factor
	//this does not work on all models though
	model = glm::scale(model, glm::vec3(std::min(1.0f / model[0].x, 1.0f)));

	model = glm::scale(model, glm::vec3(this->scale));
	model = glm::translate(model, this->position);

	//Matrix used to transform normal vectors to world coordinates
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(model));
	
	shader.setBool("maps.diffuse", diffuseCpt);
	shader.setBool("maps.height", heightCpt);
	shader.setBool("maps.opacity", opacityCpt);
	shader.setBool("maps.normal", normalCpt);

	shader.setMatrix3("normalMatrix", normalMatrix);
	shader.setMatrix4("model", model);

	glBindVertexArray(this->m_VAO);
	glDrawElements(GL_TRIANGLES, this->m_indices.size(), GL_UNSIGNED_INT,0);
	//Reset to default
	glActiveTexture(GL_TEXTURE0);
}

std::vector<Vertex> Mesh::getVertices() {
	return this->m_vertices;
}
std::vector<uint32_t> Mesh::getIndices() {
	return this->m_indices;
}

std::vector<Texture>& Mesh::getTextures(){
	return this->m_textures;
}

void Mesh::setPosition(glm::vec3 position) {
	this->position = position;
}

void Mesh::setScale(float scale){
	this->scale = scale;
}
