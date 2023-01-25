#ifndef TEXTURE_H
#define TEXTURE_H

#include <map>
#include "glad/glad.h"
#include <assimp/material.h>
#include <stb/stb_image.h>
#include <string>

class Texture
{
	public:
		static void loadTextureInMemory(std::string, aiTextureType);
		static Texture getTextureFromFile(std::string, aiTextureType);

		~Texture();

	private:
		GLuint m_texture;
		std::string m_filename;
		aiTextureType m_texture_type;
		static std::map<std::string, Texture> m_map;

		Texture(std::string, aiTextureType texture_type);

};

#endif
