#include "headers/texture.h"
#include "headers/logger.h"

std::map<std::string, Texture> Texture::m_map;



Texture::Texture(std::string filename, aiTextureType texture_type) {
    int width, height, channels;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 0);

    if (data == nullptr) {
        logger.log("Failed to load texture: " + filename);
    }

    GLenum channels_type;
    if (channels == 1) {
      channels_type = GL_RED;
    } else if (channels == 3) {
      channels_type = GL_RGB;
    } else if (channels == 4) {
      channels_type = GL_RGBA;
    }

    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    this->m_filename = filename;
    this->m_texture_type = texture_type;

    stbi_image_free(data);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_texture);
}

void Texture::loadTextureInMemory(std::string filename, aiTextureType texture_type) {
    if (!m_map.count(filename)) {
      Texture texture { filename, texture_type };
      Texture::m_map.insert(std::make_pair(filename, texture));
    }
}

Texture Texture::getTextureFromFile(std::string filename, aiTextureType texture_type) {
  if (m_map.count(filename)) {
    return Texture::m_map.at(filename);
  } else {
    loadTextureInMemory(filename, texture_type);
  }

  return Texture::m_map.at(filename);
}
