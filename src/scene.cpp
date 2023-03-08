#include "headers/scene.h"
#include "headers/light.h"
#include "headers/model.h"
#include "headers/logger.h"
#include "headers/pointLight.h"
#include "headers/cubemap.h"
#include "headers/directionalLight.h"

#include <iostream>

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

float deltaTime = 0;
bool firstMouse = true;
float lastX, lastY;

Camera camera;
bool camera_control = false;

uint16_t Scene::width = 800;
uint16_t Scene::height = 600;

Scene::Scene(uint16_t width, uint16_t height) {
    Scene::width = width;
    Scene::height = height;

    this->m_pWindow = this->initWindow();
    std::vector<DefaultGui*> list = {
        new UserParameters(true)
    };
    this->m_gui = DefaultGui(true, list);
}

Scene::~Scene() {
    this->m_gui.closeLibrary();
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

Camera Scene::getCamera() {
    return camera;
}

/*
bool& Scene::getDrawLights() {
    return this->renderOptions_draw_lights;
}
*/

void Scene::addModel(Model* model) {
    this->modelPool.push_back(model);
}

void Scene::removeModel(Model* model) {
    auto it = std::find(this->modelPool.begin(), this->modelPool.end(), model);

    if(it != this->modelPool.end())
        this->modelPool.erase(it);
}

void Scene::addLight(Light* light) {
    this->lightPool.push_back(light);
}

void Scene::removeLight(Light* light) {
    auto it = std::find(this->lightPool.begin(), this->lightPool.end(), light);

    if(it != this->lightPool.end())
        this->lightPool.erase(it);
}

std::vector<Light*> Scene::getLights() {
    return this->lightPool;
}

std::vector<Model*> Scene::getModels() {
    return this->modelPool;
}

GLFWwindow* Scene::createWindow() {

    GLFWwindow* window = glfwCreateWindow(Scene::width, Scene::height, "3D engine", NULL, NULL);

    if (window == NULL) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Define the created window as the main context
    glfwMakeContextCurrent(window);

    /*We have to tell OpenGL the size of the rendering window so
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
    
    //this->addLight(new PointLight(glm::vec3(17.0f, 17.0f, -20.0f), glm::vec3(1.0f, 1.0f, 1.0f), 2.0f, 0.5f, 0.4f,1.0f,0.014, 0.0007));
    //this->addLight(new PointLight(glm::vec3(0.0f, 0.2f, 10.0f), glm::vec3(0.949f, 0.341f, 0.675f)));
    this->addLight(new DirectionalLight(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.5f, 0.5f, 0.5f),0.5,0.3));

    //this->addModel(new Model("models/backpack/backpack.obj",glm::vec3(0.0f,0.0f,0.0f)));
    //this->addModel(new Model("models/satellite/satellite.obj", glm::vec3(8.0f,0.0f,0.0f)));
    this->addModel(new Model("models/fortressScaled/fortress.obj", glm::vec3(0.0f,-2.0f,-15.0f),1.0f,false));
    
    Shader shader{ "shaders/default.vs", "shaders/default.fs" };
    Shader lightShader{ "shaders/default.vs", "shaders/light.fs" };
    CubeMap yokohama{ "models/skybox/yokohama",std::vector<std::string>{"posx.jpg","negx.jpg","posy.jpg","negy.jpg","posz.jpg","negz.jpg"} };

    glfwSetCursorPosCallback(this->m_pWindow, mouse_callback);
    glfwSetInputMode(this->m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetKeyCallback(this->m_pWindow, key_callback);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    double current = 0;
    float lastFrame = 0.0f;

    int frame = 0;

    this->m_gui.init(m_pWindow);
    
    while (!glfwWindowShouldClose(m_pWindow)) {

        current = glfwGetTime();
        deltaTime = current - lastFrame;
        lastFrame = current;

        glClearColor(0.0f,0.0f,0.0f,0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.processInput(this->m_pWindow, deltaTime);
        camera.update();
        
        glm::mat4 projection;					   //FOV	         //Aspect ratio                              //near //far plane frustum
        projection = glm::perspective(glm::radians(camera.getFov()), (float)Scene::width / (float)Scene::height, 0.1f, 300.0f);

        //yokohama.draw(camera.getLookAtMatrix(), projection);
        
        //Must use the shader before calling glUniform()
        shader.use();

        //Model
        shader.setVec3("viewPos", camera.getPos());
        shader.setMatrix4("view", camera.getLookAtMatrix());
        shader.setMatrix4("projection", projection);

        for (Model* model : this->getModels()) {
            model->draw(shader);
        }


        //Lights
        lightShader.use();
        lightShader.setMatrix4("view", camera.getLookAtMatrix());
        lightShader.setMatrix4("projection", projection);

        for (Light* light : this->getLights()) {
            light->draw(shader,lightShader);
        };

        this->m_gui.render(this);
        
        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
 
    if (!camera_control) {
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
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        camera_control = !camera_control;

        if (!camera_control) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }

}