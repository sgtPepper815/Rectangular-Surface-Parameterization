#pragma once


#include <GLFW/glfw3.h>
#include <vector>

#include "model.h"
#include "parameterization.h"
#include "camera.h"


class Renderer
{
public:
    Renderer() = delete;
	Renderer& operator=(const Renderer&) = delete;
	Renderer& operator=(Renderer&&) = delete;

	Renderer(const std::vector<Vec3>* vertices, const std::vector<unsigned int>* indices)
		: mVertices(*vertices), mIndices(*indices) {};

    void run(GLFWwindow* window, 
        GLuint shaderProgram, 
        GLuint lineShaderProgram, 
        GLuint VAO, 
        GLuint VBO, 
        GLuint EBO, 
        GLuint lineVAO, 
        GLuint lineVBO, 
        int lineVerticesSize,
        Camera* camera);


private:
	std::vector<Vec3> mVertices;
	std::vector<unsigned int> mIndices;
};


inline void Renderer::run(GLFWwindow* window, 
    GLuint shaderProgram, 
    GLuint lineShaderProgram, 
    GLuint VAO, 
    GLuint VBO, 
    GLuint EBO, 
    GLuint lineVAO, 
    GLuint lineVBO, 
    int lineVerticesSize, 
    Camera* camera)
{
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // model matrix
        glm::mat4 model = glm::mat4(1.0f);

        // view matrix
        glm::mat4 view = camera->getViewMatrix(camera->getCameraPosition());

        // projection matrix
        glm::mat4 projection = glm::perspective(
            glm::radians(45.0f),
            800.0f / 600.0f,
            0.1f,
            100.0f
        );

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw
        glUseProgram(shaderProgram);

        // set uniforms
        glUniformMatrix4fv(
            glGetUniformLocation(shaderProgram, "model"),
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );

        glUniformMatrix4fv(
            glGetUniformLocation(shaderProgram, "view"),
            1,
            GL_FALSE,
            glm::value_ptr(view)
        );

        glUniformMatrix4fv(
            glGetUniformLocation(shaderProgram, "projection"),
            1,
            GL_FALSE,
            glm::value_ptr(projection)
        );
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glUseProgram(lineShaderProgram);
        // set uniforms
        glUniformMatrix4fv(
            glGetUniformLocation(lineShaderProgram, "model"),
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );

        glUniformMatrix4fv(
            glGetUniformLocation(lineShaderProgram, "view"),
            1,
            GL_FALSE,
            glm::value_ptr(view)
        );

        glUniformMatrix4fv(
            glGetUniformLocation(lineShaderProgram, "projection"),
            1,
            GL_FALSE,
            glm::value_ptr(projection)
        );
        glBindVertexArray(lineVAO);
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawArrays(GL_LINES, 0, lineVerticesSize);

        // glBindVertexArray(0); // no need to unbind it every time 

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
}