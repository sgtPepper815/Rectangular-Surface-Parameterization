
#include <iostream>

#include "include.h"

int main()
{
	// setup camera 
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	float cameraYaw = 45.0f;
	float cameraPitch = 45.0f;
	float cameraDistance = 3.0f;

	Camera camera(cameraTarget, cameraYaw, cameraPitch, cameraDistance);
	glm::vec3 cameraPosition = camera.getCameraPosition();
	//glm::mat4 cameraViewMatrix = camera.getViewMatrix(cameraPosition);

	GLFWBuilder glfwBuilder(camera);

	glfwBuilder.createGLFWWindow();
	glfwBuilder.initGlad();
	glfwBuilder.setupBuffers(vertices, indices);

	Parameterization parameterization;
	std::vector<Vec3> lineVertices = parameterization.calculateNormalVectorPerTriangle(vertices, indices);

	glfwBuilder.setupLineBuffers(lineVertices);

	Shader shader("shader/shader.vert", "shader/shader.frag");
	Shader blackLineShader("shader/blackLineShader.vert", "shader/blackLineShader.frag");
	Shader normalsShader("shader/normalsShader.vert", "shader/normalsShader.frag");

	Renderer renderer(&vertices, &indices);
	renderer.run(glfwBuilder.getWindow(), shader.ID, blackLineShader.ID, normalsShader.ID,
		glfwBuilder.getVAO(), glfwBuilder.getVBO(), glfwBuilder.getEBO(), 
		glfwBuilder.getLineVAO(), glfwBuilder.getLineVBO(), lineVertices.size(), &camera);



}
