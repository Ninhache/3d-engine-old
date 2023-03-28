#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    /**
     * @brief Construct a new Shader object
     *
     * @param vertexPath The path to the vertex shader
     * @param fragmentPath The path to the fragment shader
     */
    Shader(const char *vertexPath, const char *fragmentPath);

    /**
     * @brief Tells opengl to use this Shader as the program
     * This needs to be called when setting up uniforms or
     * trying to render with this shader
     *
     */
    void use();

    /**
     * @brief The functions below are used to set uniforms to the shader
     *
     * @param name The name of the uniform
     * @param value The value of the uniform
     */
    void setBool(const std::string &name, const bool value) const;
    void setInt(const std::string &name, const int value) const;
    void setFloat(const std::string &name, const float value) const;
    void setMatrix4(const std::string &name, const glm::mat4 &value) const;
    void setMatrix3(const std::string &name, const glm::mat3 &value) const;
    void setVec3(const std::string &, const glm::vec3 &value) const;
    void setVec2(const std::string &name, const glm::vec2 &value) const;

    /**
     * @brief Get the Id of the shader program
     *
     * @return int
     */
    int getId() const { return ID; }

private:
    unsigned int ID;
    /**
     * @brief Check for errors when compiling and linking shaders
     *
     * @param shader The id of the shader
     * @param type The type of the error to be checked
     * between "FRAGMENT", "VERTEX" and "PROGRAM" though the first two will call the same function
     */
    void checkCompileErrors(unsigned int shader, std::string type);
};

#endif // SHADER_H