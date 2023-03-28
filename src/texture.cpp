#include "headers/texture.h"
#include "headers/logger.h"

std::map<std::string, Texture> Texture::m_map;

Texture::Texture() {}

Texture::Texture(std::string filename, aiTextureType texture_type, bool flipTexture)
{
    int width, height, channels;

    stbi_set_flip_vertically_on_load(flipTexture);
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &channels, 0);

    if (data == nullptr)
    {
        logger.log("Failed to load texture: " + filename);
    }

    GLenum channels_type = 0;
    if (channels == 1)
    {
        channels_type = GL_RED;
    }
    else if (channels == 3)
    {
        channels_type = GL_RGB;
    }
    else if (channels == 4)
    {
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

Texture Texture::loadCubemap(std::vector<std::string> paths)
{

    Texture t;
    stbi_set_flip_vertically_on_load(false);
    glGenTextures(1, &t.m_ID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, t.m_ID);

    int width, height, nrChannels;
    for (size_t i = 0; i < paths.size(); i++)
    {
        unsigned char *data = stbi_load(paths[i].c_str(), &width, &height, &nrChannels, 0);

        if (data == nullptr)
        {
            stbi_image_free(data);
            logger.log("Failed to load texture: " + paths[i]);
            break;
        }

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return t;
}

void Texture::loadTextureInMemory(std::string filename, aiTextureType texture_type, bool flipTextures)
{
    if (!m_map.count(filename))
    {
        Texture texture{filename, texture_type, flipTextures};
        Texture::m_map.insert(std::make_pair(filename, texture));
    }
}

Texture Texture::getTextureFromFile(std::string filename, aiTextureType texture_type, bool flipTextures)
{
    loadTextureInMemory(filename, texture_type, flipTextures);
    return Texture::m_map.at(filename);
}

aiTextureType Texture::getType()
{
    return this->m_texture_type;
}

GLuint Texture::getID()
{
    return this->m_ID;
}