#include "camera.h"

Camera::Camera(glm::vec3 target, float yaw, float pitch, float distance)
	: mTarget(target), mYaw(yaw), mPitch(pitch), mDistance(distance) {}

glm::vec3 Camera::getCameraPosition()
{
	float x = mDistance * sin(mYaw) * cos(mPitch);
	float y = mDistance * sin(mPitch);
	float z = mDistance * cos(mYaw) * cos(mPitch);

	return mTarget + glm::vec3(x,y,z);
}

glm::mat4 Camera::getViewMatrix(glm::vec3 cameraPosition)
{
	return glm::lookAt(cameraPosition, mTarget, glm::vec3(0.0f, 1.0f, 0.0f));
}
