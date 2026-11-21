#include "camera.h"

Camera::Camera(glm::vec3 target, float yaw, float pitch, float distance)
	: mTarget(target), mYaw(yaw), mPitch(pitch), mDistance(distance) {}

glm::vec3 Camera::getCameraPosition() const
{
	float x = mDistance * sin(mYaw) * cos(mPitch);
	float y = mDistance * sin(mPitch);
	float z = mDistance * cos(mYaw) * cos(mPitch);

	return mTarget + glm::vec3(x, y, z);
}

glm::mat4 Camera::getViewMatrix(glm::vec3 &cameraPosition) const
{
	return glm::lookAt(cameraPosition, mTarget, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::onMouseButton(int button, int action, double x, double y)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		// we won't give glfw a chance to fuck it up
		if (action == GLFW_PRESS)
		{
			mIsRotating = true;
		}
		else if (action == GLFW_RELEASE)
		{
			mIsRotating = false;
		}

		mLastMouseX = x;
		mLastMouseY = y;
	}
}

void Camera::onMouseMove(double x, double y)
{
	double deltaX = x - mLastMouseX;
	double deltaY = y - mLastMouseY;

	mLastMouseX = x;
	mLastMouseY = y;

	if (mIsRotating)
	{
		mYaw -= static_cast<float>(deltaX) * mMouseSensitivity;
		mPitch += static_cast<float>(deltaY) * mMouseSensitivity;

		mPitch = glm::clamp(mPitch, -1.55f, 1.55f); // prevent gimbal lock - move only between aprox. -88.8 and 88.8 degrees
	}
}

void Camera::onMouseScroll(double yOffset)
{
	float zoomSpeed = 0.1f;

	mDistance *= std::exp(
		-static_cast<float>(yOffset) * zoomSpeed
	);

	mDistance = glm::clamp(mDistance, 0.2f, 50.0f);
}