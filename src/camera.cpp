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

void Camera::scrollUpdate(double yoffset) {

	fov -= (float)yoffset * scrollMult;
	if (fov > maxFov)
		fov = maxFov;
	else if (fov < minFov)
		fov = minFov;

}

void Camera::processInput(GLFWwindow* window, float deltaTime) {

	const float cameraVelocity = cameraSpeed * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraPos += cameraVelocity * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPos -= cameraVelocity * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cameraPos -= cameraVelocity * glm::normalize(cross(cameraFront, cameraUp));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cameraPos += cameraVelocity * glm::normalize(cross(cameraFront, cameraUp));
	}
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void Camera::mouseUpdate(float xoff, float yoff) {

	yaw += (xoff * mouseSensitivity);
	pitch += (yoff * mouseSensitivity);

	pitch = pitch > 89.0 ? 89.0 : pitch;
	pitch = pitch < -89.0 ? -89.0 : pitch;

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

float& Camera::getMouseSensitivity() {
	return this->mouseSensitivity;
}

float& Camera::getCameraSpeed() {
	return this->cameraSpeed;
}


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
	cameraUp = glm::normalize(glm::cross(cameraSide,cameraFront));
}
