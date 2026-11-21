#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{

public:
	Camera(glm::vec3 target, float yaw, float pitch, float distance);
	~Camera() = default;
	glm::vec3 getCameraPosition() const;
	glm::mat4 getViewMatrix(glm::vec3 &cameraPosition) const; 
	
	void onMouseButton(int button, int action, double x, double y);
	void onMouseMove(double x, double y); 
	void onMouseScroll(double yOffset);
private:
	glm::vec3 mTarget;
	float mYaw;
	float mPitch;
	float mDistance;

	bool mIsRotating = false;
	double mLastMouseX = 0.0;
	double mLastMouseY = 0.0;
	float mMouseSensitivity = 0.005f;

};