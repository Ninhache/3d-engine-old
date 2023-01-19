#include "headers/logger.h"
#include "headers/scene.h"

Core::Scene::Scene(uint16_t width, uint16_t height) {
    this->m_width = width;
    this->m_height = height;
    
    this->m_pWindow = this->initWindow();
}

Core::Scene::~Scene() {
    glfwDestroyWindow(m_pWindow);
    glfwTerminate();
}

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

void Core::Scene::initGLAD() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        exit(EXIT_FAILURE);
    }
}

void Core::Scene::renderLoop() {
    while(!glfwWindowShouldClose(m_pWindow)) {

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();    
    }
}

void Core::Scene::initWindowKeyCallback() {
    throw std::invalid_argument("Unintialized function");
}