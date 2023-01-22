#include "headers/mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Texture> textures, aiMatrix4x4 localTransform) {
	this->m_vertices = vertices;
	this->m_indices = indices;
	this->m_textures = textures;
	this->localTransform = localTransform;
	configureBuffers();
	this->a = (float)rand() / RAND_MAX;
	this->b = (float)rand() / RAND_MAX;
	this->c = (float)rand() / RAND_MAX;
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,normal));
	glEnableVertexAttribArray(2);


	glBindVertexArray(0);

}
void Mesh::draw(Shader shader) {
	//We set the correct model for the Mesh (this is the localTransform according to its parents)
	glm::mat4 model = glm::transpose(glm::make_mat4(&this->localTransform.a1));
	shader.setMatrix("model", model);
	shader.use();
	glBindVertexArray(this->m_VAO);
	glDrawElements(GL_TRIANGLES, this->m_indices.size(), GL_UNSIGNED_INT,0);
}

void Mesh::associateTextures() {

}
