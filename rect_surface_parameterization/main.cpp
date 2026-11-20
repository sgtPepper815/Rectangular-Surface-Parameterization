
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

	Shader shader("shader/shader.vert", "shader/shader.frag");

	Renderer renderer(&vertices, &indices);
	renderer.run(glfwBuilder.getWindow(), shader.ID, glfwBuilder.getVAO(), glfwBuilder.getVBO(), glfwBuilder.getEBO());



}
