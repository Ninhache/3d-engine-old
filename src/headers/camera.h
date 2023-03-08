#ifndef CAMERA_CLASS_HEADER
#define CAMERA_CLASS_HEADER

#include <glm/glm.hpp>

#include "shader.h"

class Camera {

public:
	/**
	*Updates the view matrix
	*/
	void update();
	
	/**
	@param window
	@param deltaTime - Time it took to render the last frame, helps keeping camera speed constant
	*/
	void processInput(GLFWwindow* window, float deltaTime);
	
	/**
	* Changes Field of view into values between maxFov and minFov according to yoffset
	@param yoffset - Amount scrolled vertically
	*/
	void scrollUpdate(double yoffset);
	
	/**
	* Updates yaw and pitch based on mouse coordinates which will influence camera rotation
	* The pitch is kept under 90 degrees to prevent scene from being reversed
	@param xoff - Difference between last x and current x of cursor
	@param yoff - Difference between last y and current y of cursor
	*/
	void mouseUpdate(float xoff, float yoff);

	/**
	* Updates camera x,y,z directional vectors
	*/
	void updateVectors();

	float getFov();
	glm::vec3 getPos();
	glm::mat4 getLookAtMatrix();
	float& getMouseSensitivity();
	float& getCameraSpeed();
	
private:
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraSide = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::mat4 view = glm::mat4(1.0f);

	float sWidth = 800, sHeight = 600, mouseSensitivity = 0.1f, cameraSpeed = 6.0f, scrollMult=0.2;
	const float maxFov = 45.6, minFov = 44.4;
	float yaw = -90.0f, pitch = 0.0f, fov = 45.0f;
};

#endif