#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include "settings.h"
#include "vec.h"
#include "camera.h"

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    Camera* camera = static_cast<Camera*>(
        glfwGetWindowUserPointer(window)
        );

    if (!camera)
        return;

    double x, y;
    glfwGetCursorPos(window, &x, &y);

    camera->onMouseButton(button, action, x, y);
}

void cursorPositionCallback(GLFWwindow* window, double x, double y)
{
    Camera* camera = static_cast<Camera*>(
        glfwGetWindowUserPointer(window)
        );

    if (!camera)
        return;

    camera->onMouseMove(x, y);
}

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
    Camera* camera = static_cast<Camera*>(
        glfwGetWindowUserPointer(window)
        );

    if (!camera)
        return;

    camera->onMouseScroll(yOffset);
}



class GLFWBuilder
{
public:
    GLFWBuilder(Camera& camera);
    ~GLFWBuilder() = default;

	GLFWBuilder& operator=(const GLFWBuilder&) = delete;
	GLFWBuilder& operator=(GLFWBuilder&&) = delete;

    void createGLFWWindow();
    void initGlad();
    void setupBuffers(const std::vector<Vec3> vertices, const std::vector<unsigned int> indices);
    void setupLineBuffers(const std::vector<Vec3> vertices);

    GLFWwindow* getWindow() const { return mWindow; };

    unsigned int getVAO() const { return meshVAO; };
    unsigned int getVBO() const { return meshVBO; };
    unsigned int getEBO() const { return meshEBO; };

    unsigned int getLineVAO() const { return lineVAO; };
    unsigned int getLineVBO() const { return lineVBO; };

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void key_input_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
    GLFWwindow* mWindow;
    unsigned int meshVBO, meshVAO, meshEBO;
    unsigned int lineVBO, lineVAO;

    Camera* mCamera;
};

inline GLFWBuilder::GLFWBuilder(Camera& camera)
    : mCamera(&camera)
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

}

inline void GLFWBuilder::createGLFWWindow()
{
    // glfw window creation
   // --------------------
    mWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Rectangular Surface Parameterization", NULL, NULL);
    if (mWindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(mWindow);

    if (mCamera == nullptr)
    {
		std::cout << "Camera pointer is null" << __FUNCTION__ << std::endl;
		glfwTerminate();
        return;
    }

    glfwSetWindowUserPointer(mWindow, mCamera);

	glfwSetMouseButtonCallback(mWindow, mouseButtonCallback);
	glfwSetCursorPosCallback(mWindow, cursorPositionCallback); 
    glfwSetScrollCallback(mWindow, scrollCallback);

    glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);
    glfwSetKeyCallback(mWindow, key_input_callback);

}

inline void GLFWBuilder::initGlad()
{
    // glad: load all OpenGL function pointers
   // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glEnable(GL_DEPTH_TEST);
}

inline void GLFWBuilder::setupBuffers(const std::vector<Vec3> vertices, const std::vector<unsigned int> indices)
{
    glGenVertexArrays(1, &meshVAO);
    glGenBuffers(1, &meshVBO);
    glGenBuffers(1, &meshEBO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(meshVAO);

    glBindBuffer(GL_ARRAY_BUFFER, meshVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vec3), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

}

inline void GLFWBuilder::setupLineBuffers(const std::vector<Vec3> vertices)
{
    glGenVertexArrays(1, &lineVAO);
    glGenBuffers(1, &lineVBO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(lineVAO);

    glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vec3), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

}

inline void GLFWBuilder::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

inline void GLFWBuilder::key_input_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}
