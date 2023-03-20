#define DOCTEST_CONFIG_IMPLEMENT

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "headers/doctest.h"
#include "../src/headers/model.h"
#include "../src/headers/cubemap.h"

GLFWwindow* initTest(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(1,1, "3D engine Test", NULL, NULL);

	if (window == NULL)
		glfwTerminate();

	glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    return window;
}  

int main(int argc, char** argv) {

    doctest::Context context;

    GLFWwindow* window = initTest();
    int res = context.run(); // run

    if(context.shouldExit()){
        glfwTerminate();
        return res;         
    } 
    
    //Clear
    glfwTerminate();
    glfwDestroyWindow(window);

    return res; // the result from doctest is propagated here as well
}


TEST_CASE("testing the model loading") {

    Model model{"../models/test/quad.obj"};
    //Root model should not have meshes
    CHECK(model.getMeshes().size() == 0);

    CHECK(model.getChildren().size() == 1);
    Model child = model.getChildren()[0];
    CHECK(child.getMeshes().size() == 1); 

    Mesh quadMesh = child.getMeshes()[0];
    CHECK(quadMesh.getVertices().size() == 4);
    CHECK(quadMesh.getIndices().size() == 6);

    std::vector<Texture>& textures = quadMesh.getTextures();
    CHECK(textures.size() == 1);
    CHECK(textures[0].getType() == aiTextureType_DIFFUSE);

}

TEST_CASE("testing the model updating") {
    
    Model model{"../models/test/quad.obj"};
    Model& children = model.getChildren()[0];


    model.setPosition(glm::vec3(1.0f));
    CHECK(model.getPosition() == glm::vec3(1.0f));
    //Position should propagate to all children
    CHECK(children.getPosition() == glm::vec3(1.0f));
    
    model.setScale(1.5f);
    CHECK(model.getScale() == 1.5f);
    CHECK(children.getScale() == 1.5f);

    CHECK(!model.isOutlined());
    model.setOutlined(true);
    CHECK(model.isOutlined());

}

TEST_CASE("testing the shader loading") {
	Shader shader{ "../shaders/default.vs", "../shaders/default.fs" };
    CHECK(shader.getId() > 0);
}