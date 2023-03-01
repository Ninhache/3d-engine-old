#include "headers/scene.h"
#include "headers/light.h"
#include "headers/logger.h"
#include "headers/pointLight.h"
#include "headers/cubemap.h"
#include "headers/directionalLight.h"

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
    std::vector<DefaultGui*> list = { new UserParameters(true) };
    this->m_gui = DefaultGui(true, list);
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

Camera Scene::getCamera() {
    return camera;
}

bool& Scene::getDrawLights() {
    return this->renderOptions_draw_lights;
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
    
    Light* lights[] = {
        new PointLight(glm::vec3(2.0f, 0.2f, 0.3f), glm::vec3(0.549f, 0.110f, 0.353f)),
        new PointLight(glm::vec3(-2.0f, 0.2f, 0.3f), glm::vec3(0.949f, 0.341f, 0.675f)),
        new PointLight(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.016f, 0.749f, 0.749f)),
        new DirectionalLight(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.5f, 0.5f, 0.5f), 0.5f, 0.1f)
    };

    Model models[] = { 
        Model("models/backpack/backpack.obj",glm::vec3(-3.0f,0.0f,0.0f)), 
        Model("models/blitz.fbx", glm::vec3(3.0f,0.0f,0.0f)),
        Model("models/raptor/Raptor.fbx", glm::vec3(6.0f,0.0f,0.0f)),
    };
    
    Shader shader{ "shaders/default.vs", "shaders/default.fs" };
    Shader lightShader{ "shaders/default.vs", "shaders/light.fs" };
    CubeMap yokohama{ "models/skybox/yokohama",std::vector<std::string>{"posx.jpg","negx.jpg","posy.jpg","negy.jpg","posz.jpg","negz.jpg"} };

    glfwSetCursorPosCallback(this->m_pWindow, mouse_callback);
    glfwSetInputMode(this->m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetKeyCallback(this->m_pWindow, key_callback);

    double current = 0;
    float lastFrame = 0.0f;

    int frame = 0;
    glEnable(GL_DEPTH_TEST);

    this->m_gui.init(m_pWindow);
    
    while (!glfwWindowShouldClose(m_pWindow)) {

        current = glfwGetTime();
        deltaTime = current - lastFrame;
        lastFrame = current;

        glClearColor(0.0f,0.0f,0.0f,0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.processInput(this->m_pWindow, deltaTime);
        camera.update();
        
        glm::mat4 projection;					   //FOV	         //Aspect ratio
        projection = glm::perspective(glm::radians(camera.getFov()), (float)Scene::width / (float)Scene::height, 0.1f, 100.0f);

        yokohama.draw(camera.getLookAtMatrix(), projection);
        
        //Must use the shader before calling glUniform()
        shader.use();

        //Model
        shader.setVec3("viewPos", camera.getPos());
        shader.setMatrix4("view", camera.getLookAtMatrix());
        shader.setMatrix4("projection", projection);
        
        for (Model model : models) {
            model.draw(shader);
        }


        //Lights
        lightShader.use();
        lightShader.setMatrix4("view", camera.getLookAtMatrix());
        lightShader.setMatrix4("projection", projection);

        for (Light* light : lights) {
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