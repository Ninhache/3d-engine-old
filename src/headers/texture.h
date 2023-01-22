#ifndef TEXTURE_H
#define TEXTURE_H

#include <map>
#include "glad/glad.h"
#include <stb/stb_image.h>

class Texture
{
	public:
		static void loadTextureInMemory(std::string);
		static Texture getTextureFromFile(std::string);
		static void unloadTexture(std::string);

		int getWidth() { return m_width; }
		int getHeight() { return m_height; }
		int getChannels() { return m_channels; }

		~Texture();

	private:
		GLuint m_texture;
		int m_width, m_height, m_channels;
		std::string m_filename;
		static std::map<std::string, Texture*> m_map;

		Texture(std::string);
		
};

#endif