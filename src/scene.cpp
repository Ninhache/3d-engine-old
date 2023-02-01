#include "headers/scene.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

float deltaTime = 0;
bool firstMouse = true;
float lastX, lastY;

Camera camera;

Scene::Scene(uint16_t width, uint16_t height) {
    this->m_width = width;
    this->m_height = height;

    this->m_pWindow = this->initWindow();
}

Scene::~Scene() {
    glfwDestroyWindow(m_pWindow);
    glfwTerminate();
}

GLFWwindow* Scene::initWindow() {
    Scene::initGLFW();
    GLFWwindow* window = Scene::createWindow();
    Scene::initGLAD();

    return window;
}

void Scene::initGLFW() {
    glfwInit();

    // Define OpenGl version to use
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* Scene::createWindow() {

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

void Scene::initGLAD() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        exit(EXIT_FAILURE);
    }
}

void Scene::renderLoop() {
    Model model{ "../models/backpack/backpack.obj" };
    Shader shader{ "../shaders/default.vs", "../shaders/default.fs" };

    glfwSetCursorPosCallback(this->m_pWindow, mouse_callback);
    glfwSetInputMode(this->m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    double current = 0;
    float lastFrame = 0.0f;

    int frame = 0;
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(m_pWindow)) {

        current = glfwGetTime();
        deltaTime = current - lastFrame;
        lastFrame = current;

        glClearColor(0.1f, 0.5f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.processInput(this->m_pWindow, deltaTime);
        camera.update();
        
        glm::mat4 projection;					   //FOV	         //Aspect ratio
        projection = glm::perspective(glm::radians(camera.getFov()), (float)m_width / (float)m_height, 0.1f, 100.0f);

        shader.setMatrix("view", camera.getLookAtMatrix());
        shader.setMatrix("projection", projection);

        model.draw(shader);

        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
 
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.mouseUpdate(xoffset, yoffset);
}