#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
    public:
        Shader(const char* vertexPath, const char* fragmentPath);
        void use();
        void setBool(const std::string&, const bool&) const;
        void setInt(const std::string&, const int&) const;
        void setFloat(const std::string&, const float&) const;
        void setMatrix(const std::string&, const glm::mat4&) const;
        int getId() const { return ID; }

    private:
        unsigned int ID;
        void checkCompileErrors(unsigned int shader, std::string type);
};
#endif