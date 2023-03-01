#ifndef SCENE_H
#define SCENE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "camera.h"
#include "model.h"
#include "gui.h"

class Scene {
    
public:
    Scene(uint16_t, uint16_t);
    ~Scene();
    
    /**
     * @brief Setup a callback for when the user press a key
     * 
     */
    void initWindowKeyCallback();

    /**
     * @brief Launch the render loop, doesnt initialize anything, just launching the loop
     * 
     */
    void renderLoop();

    uint16_t getWidth() { return m_width; }
    uint16_t getHeight() { return m_height; }
    void setWidth(uint16_t width) { this->m_width = width; }
    void setHeight(uint16_t height) { this->m_height = height; }
    bool& getDrawLights();
    Camera getCamera();

private:
    uint16_t m_width;
    uint16_t m_height;
    GLFWwindow* m_pWindow;
    DefaultGui m_gui;
    bool renderOptions_draw_light = true;

    /**
     * @brief Init all the libraries and generate a windows
     * 
     * @return GLFWwindow* 
     */
    GLFWwindow* initWindow();

    /**
     * @brief init the GLFW Library : 
     * GLFW provides a simple API for creating windows, contexts and surfaces, receiving input and events
     */
    void initGLFW();

    /**
     * @brief create a window from glfw
     * 
     * @return GLFWwindow* program can exit if window finish as null
     */
    GLFWwindow* createWindow();

    /**
     * @brief Init the GLAD Library : 
     * GLAD manages function pointers for OpenGL so we want to initialize GLAD before we call any OpenGL function.
     */
    void initGLAD();
    
    /**
     * @brief Setup a callback for when the user resize the window
     * 
     * @param window 
     * @param width 
     * @param height 
     */
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }
    
};

#endif