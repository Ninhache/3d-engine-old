#include <glad/glad.h>
#include <vector>
#include "shader.h"

class Framebuffer
{
public:
	Framebuffer(int width, int height, int nbAttachments, bool depthBuffer = false);
	void setInputTextures(Shader& shader, int size);
	void setOuputTexture(int position);
	void use(int width, int height);
private:
	std::vector<unsigned int> colorAttachements;
	unsigned int m_ID, m_rbo, m_depthBufferID;
	int m_width, m_height;
	std::string m_textureName;
	//This bool is true if the depth buffer needs to be read
	bool m_depthBuffer;
};