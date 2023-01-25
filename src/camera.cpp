#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "headers/shader.h"
#include "headers/camera.h"
#include <iostream>

/**
* Don't put **this->** on members of this class it will only create confusion since there are too many
*/
void Camera::update() {
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}


/**
* Changes Field of view into values between maxFov and minFov according to yoffset
@param yoffset - Amount scrolled vertically
*/
void Camera::scrollUpdate(double yoffset) {

	fov -= (float)yoffset * scrollMult;
	if (fov > maxFov)
		fov = maxFov;
	else if (fov < minFov)
		fov = minFov;

	std::cout << fov << std::endl;

}

/**
@param window
@param deltaTime - Time it took to render the last frame, helps keeping camera speed constant
*/
void Camera::processInput(GLFWwindow* window, float deltaTime) {

	const float cameraSpeed = cameraSensitivity * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraPos += cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPos -= cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cameraPos -= cameraSpeed * cameraSide;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cameraPos += cameraSpeed * cameraSide;
	}

}

/**
* Updates yaw and pitch based on mouse coordinates which will influence camera rotation
* The pitch is kept under 90 degrees to prevent scene from being reversed
@param xoff - Difference between last x and current x of cursor
@param yoff - Difference between last y and current y of cursor
*/
void Camera::mouseUpdate(float xoff, float yoff) {

	yaw += (xoff * mouseSensitivity);
	pitch += (yoff * mouseSensitivity);

	pitch = pitch > 89.0f ? 89.0f : pitch;
	pitch = pitch < -89.0f ? -89.0f : pitch;

	updateVectors();
}

glm::mat4 Camera::getLookAtMatrix() {
	return view;
}

glm::vec3 Camera::getPos() {
	return cameraPos;
}

float Camera::getFov() {
	return fov;
}

/**
* Updates camera x,y,z directional vectors
*/
void Camera::updateVectors() {

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);

	//This gives us an orthogonal vector between cameraFront (indicating where the camera is facing)
	//and the world Up vector (pointing toward +Y) which gives us the X axis vector relative to the camera
	cameraSide = glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f,1.0f,0.0f)));
	//Same logic as cameraSide
	cameraUp = glm::normalize(glm::cross(cameraFront, cameraSide));
}
