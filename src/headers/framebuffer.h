#include <glad/glad.h>

class Framebuffer
{
public:
	Framebuffer(int width, int height);
	void bindTexture();
	void use(int width, int height);

private:
	unsigned int m_ID;
	unsigned int m_textureBufferID;
	unsigned int m_rbo;
	int m_width, m_height;
};