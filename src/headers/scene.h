#ifndef SCENE_H
#define SCENE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "camera.h"
#include "model.h"
#include "gui.h"
#include "light.h"
#include "framebuffer.h"
#include "cubemap.h"
#include "postProcessing.h"

class Scene {
    
public:

    Scene(uint16_t width, uint16_t height);

    /**
     * @brief Destructor cleans the libraries
    */
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

    // Non sense function
    // bool& getDrawLights();
    Camera getCamera();

    /**
     * @brief Add a model to the scene
     * 
     * @param model
    */
    void addModel(Model*);

    /**
     * @brief Remove a model to the scene
     * 
     * @param model
    */
    void removeModel(Model*);

    /**
     * @brief Remove a light to the scene
     * 
     * @param light
    */
    void addLight(Light*);

    /**
     * @brief Remove a light to the scene
     * 
     * @param light
    */
    void removeLight(Light*);

    void addShader(std::string name, Shader* shader);
    void addCubemap(std::string name, CubeMap* cubemap);
    void addFramebuffer(std::string name, Framebuffer* framebuffer);
    void setupScene();

    std::vector<Light*> getLights();
    std::vector<Model*> getModels();
    PostProcessing& getProcessing();
    std::map<std::string, Shader*> getShaders();
    bool& getBool(std::string name);

    static uint16_t width;
    static uint16_t height;

private:
    GLFWwindow* m_pWindow;
    DefaultGui m_gui;
    // bool renderOptions_draw_lights = true;
    std::vector<Light*> lightPool;
    std::vector<Model*> modelPool;
    std::map<std::string, Shader*> m_shaders;
    std::map<std::string, CubeMap*> m_cubemaps;
    std::map<std::string, Framebuffer*> m_framebuffers;
    PostProcessing pProcessing;

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
        Scene::width = width;
        Scene::height = height;
    }

    void drawScene(std::string shaderName);
    
};

extern Camera camera;

#endif