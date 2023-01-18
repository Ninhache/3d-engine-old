#ifndef SCENE_H
#define SCENE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Core {
    
    class Scene {
            
        public:
            Scene(uint16_t width, uint16_t height);
            ~Scene();
            
            void initWindowCallback();
            void renderLoop();
            uint16_t getWidth() { return m_width; }
            uint16_t getHeight() { return m_height; }
            void setWidth(uint16_t width) { this->m_width = width; }
            void setHeight(uint16_t height) { this->m_height = height; }

        private:
            uint16_t m_width;
            uint16_t m_height;
            GLFWwindow* m_window;

            GLFWwindow* initWindow();
            void initGLFW();
            GLFWwindow* createWindow();
            void initGLAD();
            
            static void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
                glViewport(0, 0, width, height);
            }
            
        };

}

#endif