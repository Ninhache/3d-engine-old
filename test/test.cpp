#define DOCTEST_CONFIG_IMPLEMENT

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "headers/doctest.h"
#include "../src/headers/model.h"
#include "../src/headers/directionalLight.h"
#include "mock/cubemapMock.h"
#include "mock/cameraMock.h"

GLFWwindow *initTest()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(1, 1, "3D engine Test", NULL, NULL);

    if (window == NULL)
        glfwTerminate();

    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    return window;
}

int main(int argc, char **argv)
{

    doctest::Context context;

    GLFWwindow *window = initTest();
    int res = context.run(); // run

    if (context.shouldExit())
    {
        glfwTerminate();
        return res;
    }

    // Clear
    glfwTerminate();
    glfwDestroyWindow(window);

    return res; // the result from doctest is propagated here as well
}

TEST_CASE("testing the model & texture loading")
{

    REQUIRE(glGetError() == GL_NO_ERROR);
    Model model{"../models/test/quad.obj"};
    CHECK(glGetError() == GL_NO_ERROR);

    REQUIRE(model.getChildren().size() > 0);

    // Root model should not have meshes
    CHECK(model.getMeshes().size() == 0);

    CHECK(model.getChildren().size() == 1);
    Model child = model.getChildren()[0];
    CHECK(child.getMeshes().size() == 1);

    Mesh quadMesh = child.getMeshes()[0];
    CHECK(quadMesh.getVertices().size() == 4);
    CHECK(quadMesh.getIndices().size() == 6);

    std::vector<Texture> &textures = quadMesh.getTextures();
    CHECK(textures.size() == 1);
    CHECK(textures[0].getType() == aiTextureType_DIFFUSE);
}

TEST_CASE("testing the model updating")
{

    REQUIRE(glGetError() == GL_NO_ERROR);
    Model model{"../models/test/quad.obj"};
    CHECK(glGetError() == GL_NO_ERROR);

    Model &children = model.getChildren()[0];

    model.setPosition(glm::vec3(1.0f));

    CHECK(model.getPosition() == glm::vec3(1.0f));
    // Position should propagate to all children
    CHECK(children.getPosition() == glm::vec3(1.0f));

    model.setScale(1.5f);
    CHECK(model.getScale() == 1.5f);
    CHECK(children.getScale() == 1.5f);

    CHECK(!model.isOutlined());
    model.setOutlined(true);
    CHECK(model.isOutlined());
}

TEST_CASE("testing the shader loading")
{

    REQUIRE(glGetError() == GL_NO_ERROR);
    Shader shader{"../shaders/default.vs", "../shaders/default.fs"};
    CHECK(glGetError() == GL_NO_ERROR);

    CHECK(shader.getId() > 0);
}

TEST_CASE("testing cubemap loading")
{

    REQUIRE(glGetError() == GL_NO_ERROR);
    CubemapMock cubemap{"../models/skybox/yokohama", std::vector<std::string>{"posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg"}};
    CHECK(glGetError() == GL_NO_ERROR);

    CHECK(cubemap.getTextureId() > 0);
    CHECK(cubemap.getShaderId() > 0);
    CHECK(cubemap.getVertices().size() == 108);
}

TEST_CASE("testing camera rotation")
{

    CameraMock camera{};
    camera.setMouseSensitivity(1.0f);

    REQUIRE(camera.getMouseSensitivity() == 1.0f);

    CHECK(camera.getYaw() == -90.0f);
    CHECK(camera.getPitch() == .0f);

    camera.mouseUpdate(100.0f, 2.0f);

    CHECK(camera.getYaw() == 10.0f);
    CHECK(camera.getPitch() == 2.0f);

    camera.mouseUpdate(.0f, 90.0f);
    // should not go higher than 89
    CHECK(camera.getPitch() == 89.0f);
}

TEST_CASE("testing the shader uniform updating for the model matrix")
{

    REQUIRE(glGetError() == GL_NO_ERROR);
    Model model{"../models/test/quad.obj"};
    CHECK(glGetError() == GL_NO_ERROR);

    Shader shader{"../shaders/default.vs", "../shaders/default.fs"};
    shader.use();
    model.setPosition(glm::vec3(1.0, 0.3, 0.7));
    model.draw(shader);

    GLuint location = glGetUniformLocation(shader.getId(), "model");
    GLfloat uniformMatrix[16];
    glGetUniformfv(shader.getId(), location, uniformMatrix);

    glm::mat4 actualMatrix = glm::make_mat4(uniformMatrix);
    glm::mat4 expectedMatrix = glm::translate(glm::mat4(1.0), glm::vec3(1.0, 0.3, 0.7));
    CHECK(expectedMatrix == actualMatrix);
}

TEST_CASE("testing the light uniforms updating")
{

    REQUIRE(glGetError() == GL_NO_ERROR);
    DirectionalLight dLight{glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.5f, 0.5f, 0.5f), 0.3, 0.2};
    Shader shader{"../shaders/default.vs", "../shaders/default.fs"};
    shader.use();
    CHECK(glGetError() == GL_NO_ERROR);

    dLight.setUniforms(shader);
    
    GLuint dirLocation = glGetUniformLocation(shader.getId(), "dLight[0].lightDir");
    GLuint colorLocation = glGetUniformLocation(shader.getId(), "dLight[0].lightColor");
    GLuint ambiantLocation = glGetUniformLocation(shader.getId(), "dLight[0].ambiantStr");
    GLuint specularLocation = glGetUniformLocation(shader.getId(), "dLight[0].specularStr");
    GLuint activeLocation = glGetUniformLocation(shader.getId(), "dLight[0].activeLight");
    
    glm::vec3 color(0.0f);
    glm::vec3 lightDir(0.0f);
    GLfloat ambiantStr, specularStr;
    GLuint active;

    glGetUniformfv(shader.getId(), colorLocation, &color[0]);
    glGetUniformfv(shader.getId(), dirLocation, &lightDir[0]);
    glGetUniformfv(shader.getId(), ambiantLocation, &ambiantStr);
    glGetUniformfv(shader.getId(), specularLocation, &specularStr);
    glGetUniformuiv(shader.getId(), activeLocation, &active);

    CHECK(glm::vec3(0.5f, 0.5f, 0.5f) == color);
    CHECK(glm::vec3(-0.2f, -1.0f, -0.3f) == lightDir);
    CHECK(0.2f == ambiantStr);
    CHECK(0.3f == specularStr);
    CHECK(true == active);
}
