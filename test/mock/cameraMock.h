#ifndef CAMERA_MOCK_CLASS_HEADER
#define CAMERA_MOCK_CLASS_HEADER

#include "../../src/headers/camera.h"

class CameraMock : public Camera
{
public:
    CameraMock() : Camera(){}
	float getYaw(){ return this->yaw; }
    float getPitch(){ return this->pitch; }
    void setMouseSensitivity(float sensitivity) { this->mouseSensitivity = sensitivity;}
};

#endif // CAMERA_MOCK_CLASS_HEADER