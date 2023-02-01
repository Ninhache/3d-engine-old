#ifndef CAMERA_CLASS_HEADER
#define CAMERA_CLASS_HEADER
#include <glm/glm.hpp>
#include "shader.h"

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
	glm::mat4 view = glm::mat4(1.0f);

	float sWidth = 800, sHeight = 600, mouseSensitivity = 0.1f, cameraSensitivity = 8.0f, scrollMult=0.2;
	const float maxFov = 45.6, minFov = 44.4;
	float yaw = -90.0f, pitch = 0.0f, fov = 45.0f;
};

#endif
