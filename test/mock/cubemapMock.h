#ifndef CUBEMAP_MOCK_HEADER_FILE
#define CUBEMAP_MOCK_HEADER_FILE

#include "../../src/headers/cubemap.h"
#include "../../src/headers/shader.h"

class CubemapMock : public CubeMap
{
public:
	CubemapMock(std::string dir, std::vector<std::string> paths){
		for(std::string& path : paths)
		{
			path = dir + "/" + path;
		}
		this->m_texture = Texture::loadCubemap(paths);
    	this->shader = std::make_unique<Shader>("../shaders/cubemap.vs","../shaders/cubemap.fs");
	}

	int getTextureId(){
		return this->m_texture.getID();
	}
	int getShaderId(){
		return this->shader->getId();
	}
	std::vector<float> getVertices(){
		return this->m_vertices;
	}
};

#endif // CUBEMAP_MOCK_HEADER_FILE