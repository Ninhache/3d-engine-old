#include "headers/texture.h"
#include "headers/logger.h"

std::map<std::string, Texture> Texture::m_map;



Texture::Texture(std::string filename, aiTextureType texture_type) {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 0);

    if (data == nullptr) {
        logger.log("Failed to load texture: " + filename);
    }

    GLenum channels_type = 0;
    if (channels == 1) {
      channels_type = GL_RED;
    } else if (channels == 3) {
      channels_type = GL_RGB;
    } else if (channels == 4) {
      channels_type = GL_RGBA;
    }

    glGenTextures(1, &this->m_ID);
    glBindTexture(GL_TEXTURE_2D, this->m_ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, channels_type, width, height, 0, channels_type, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    this->m_filename = filename;
    this->m_texture_type = texture_type;

    stbi_image_free(data);
}

void Texture::loadTextureInMemory(std::string filename, aiTextureType texture_type) {
    if (!m_map.count(filename)) {
      Texture texture { filename, texture_type };
      Texture::m_map.insert(std::make_pair(filename, texture));
    }
}

Texture Texture::getTextureFromFile(std::string filename, aiTextureType texture_type) {
   
    loadTextureInMemory(filename, texture_type);
  
   return Texture::m_map.at(filename);
}

aiTextureType Texture::getType() {
    return this->m_texture_type;
}

GLuint Texture::getID() {
    return this->m_ID;  
}