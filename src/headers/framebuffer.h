#include <glad/glad.h>
#include "shader.h"

class Framebuffer
{
public:
	Framebuffer(int width, int height, std::string textureName, bool depthBuffer = false);
	void bindTexture(Shader& shader);
	void use(int width, int height);

private:
	unsigned int m_ID, m_rbo, m_textureBufferID, m_depthBufferID;
	int m_width, m_height;
	std::string m_textureName;
	//This bool is true if the depth buffer needs to be read
	bool m_depthBuffer;
};