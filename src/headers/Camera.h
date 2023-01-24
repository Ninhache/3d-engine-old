#ifndef CAMERA_CLASS_HEADER
#define CAMERA_CLASS_HEADER
#include <glm/glm.hpp>
#include "Shader.h"
#include "Scene.h"

class Camera {

public:
	void update();
	void processInput(GLFWwindow* window, float deltaTime);
	void scrollUpdate(double yoffset);
	void mouseUpdate(float xoff, float yoff);
	void updateVectors();
	float getFov();
	glm::vec3 getPos();
	glm::mat4 getLookAtMatrix();
private:

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraSide = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::mat4 view;

	float fov = 45.0f;
	const float minFov = 44.4, maxFov = 45.6, scrollMult = 0.2, cameraSensitivity = 8.0f;
	float yaw = -90.0f, pitch = 0.0f, mouseSensitivity = 0.2f; 
};

#endif