
#include <iostream>

#include "glfwbuilder.h"
#include "shader.h"
#include "model.h"
#include "renderer.h"
#include "settings.h"

int main()
{
	GLFWBuilder glfwBuilder;

	glfwBuilder.createGLFWWindow();
	glfwBuilder.initGlad();
	glfwBuilder.setupBuffers(vertices, indices);


	Parameterization parameterization;
	std::vector<Vec3> lineVertices = parameterization.calculateNormalVectorPerTriangle(vertices, indices);

	std::cout << lineVertices.data() << std::endl;

	glfwBuilder.setupLineBuffers(lineVertices);

	Shader shader("shader/shader.vert", "shader/shader.frag");
	Shader lineShader("shader/lineShader.vert", "shader/lineShader.frag");

	Renderer renderer(&vertices, &indices);
	renderer.run(glfwBuilder.getWindow(), shader.ID, lineShader.ID,
		glfwBuilder.getVAO(), glfwBuilder.getVBO(), glfwBuilder.getEBO(), 
		glfwBuilder.getLineVAO(), glfwBuilder.getLineVBO(), lineVertices.size());



}
