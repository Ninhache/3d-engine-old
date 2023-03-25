#include "headers/framebuffer.h"

Framebuffer::Framebuffer(int width, int height, std::string textureName, bool depthBuffer)
{
	this->m_width = width;
	this->m_height = height;
	this->m_depthBuffer = depthBuffer;
	this->m_textureName = textureName;

	glGenFramebuffers(1, &this->m_ID);
	glBindFramebuffer(GL_FRAMEBUFFER, this->m_ID);

	glGenTextures(1, &this->m_textureBufferID);
	glBindTexture(GL_TEXTURE_2D, this->m_textureBufferID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Unbind
	glBindTexture(GL_TEXTURE_2D, 0);
	//attach to framebuffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->m_textureBufferID, 0);

	if (depthBuffer) {
		glGenTextures(1, &this->m_depthBufferID);
		glBindTexture(GL_TEXTURE_2D, this->m_depthBufferID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//Unbind
		glBindTexture(GL_TEXTURE_2D, 0);
		//attach to framebuffer
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->m_depthBufferID, 0);
	}
	/*Stencil and depth*/
	else {
		glGenRenderbuffers(1, &this->m_rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, this->m_rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		//Unbind
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->m_rbo);
	}

	//unbind
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::use(int width, int height) {
	//We need to recreate the texture buffer if the dimension of the scene changes
	if (this->m_width != width || this->m_height != height) {
		glBindTexture(GL_TEXTURE_2D, this->m_textureBufferID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		glBindRenderbuffer(GL_RENDERBUFFER, this->m_rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, this->m_ID);
}

void Framebuffer::bindTexture(Shader& shader) {
	
	shader.use();
	if (this->m_depthBuffer) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, this->m_depthBufferID);
		shader.setInt("depthBufferTexture", 1);
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->m_textureBufferID);
	shader.setInt(this->m_textureName, 0);
}