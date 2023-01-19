#include "headers/logger.h"
#include "headers/scene.h
#include <iostream>

Core::Scene::Scene(uint16_t width, uint16_t height) {
    this->m_width = width;
    this->m_height = height;
    
    this->m_window = this->initWindow();
}

Core::Scene::~Scene() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

/**
 * @brief Init all the libraries and generate a windows
 * 
 * @return GLFWwindow* 
 */
GLFWwindow* Core::Scene::initWindow() {
    Core::Scene::initGLFW();
    GLFWwindow* window = Core::Scene::createWindow();
    Core::Scene::initGLAD();

    return window;
}

void Core::Scene::initGLFW() {
    glfwInit();

    // Define OpenGl version to use
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

/**
 * @brief create a window from glfw
 * 
 * @return GLFWwindow* program can exit if window finish as null
 */
GLFWwindow* Core::Scene::createWindow() {
    
    GLFWwindow* window = glfwCreateWindow(this->m_width, this->m_height, "3D engine", NULL, NULL);
    
    if (window == NULL) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Define the created window as the main context
    glfwMakeContextCurrent(window);
    
    /*Before we can start rendering we have to do one last thing.
    We have to tell OpenGL the size of the rendering window so
    OpenGL knows how we want to display the data and coordinates with respect to the window*/ 
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    
    return window;
}

/**
 * @brief Init the GLAD Library : 
 * GLAD manages function pointers for OpenGL so we want to initialize GLAD before we call any OpenGL function.
 */
void Core::Scene::initGLAD() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        exit(EXIT_FAILURE);
    }
}

void Core::Scene::renderLoop() {
    while(!glfwWindowShouldClose(m_window)) {

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(m_window);
        glfwPollEvents();    
    }
}