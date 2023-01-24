#include "headers/texture.h"
#include "headers/logger.h"

std::map<std::string, Texture*> Texture::m_map;

Texture::Texture(std::string filename) {
    int width, height, channels;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
    
    if (data == nullptr) {
        logger.log("Failed to load texture: " + filename);
    }

    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    this->m_width = width;
    this->m_height = height;
    this->m_channels = channels;
    this->m_filename = filename;

    stbi_image_free(data);
}

Texture::~Texture() {
    unloadTexture(m_filename);
    glDeleteTextures(1, &m_texture);
}

void Texture::loadTextureInMemory(std::string filename) {
    Texture* texture = new Texture(filename);
    Texture::m_map.insert(std::make_pair(filename, texture));
}

Texture Texture::getTextureFromFile(std::string filename) {
    try {
        return *Texture::m_map.at(filename);
    } catch(const std::exception& e) {
        loadTextureInMemory(filename);
    }

    return *Texture::m_map.at(filename);
}

void Texture::unloadTexture(std::string filename) {
    try {
        Texture* texture = Texture::m_map.at(filename);
        Texture::m_map.erase(filename);
        free(texture);
    } catch(const std::exception& e) { return; }
}