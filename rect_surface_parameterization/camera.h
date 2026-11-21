#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{

public:
	Camera(glm::vec3 target, float yaw, float pitch, float distance);
	~Camera() = default;
	glm::vec3 getCameraPosition();
	glm::mat4 getViewMatrix(glm::vec3 cameraPosition);
private:
	glm::vec3 mTarget;
	float mYaw;
	float mPitch;
	float mDistance;

};