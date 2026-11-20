#pragma once


#include <GLFW/glfw3.h>
#include <vector>

#include "model.h"
#include "parameterization.h"


class Renderer
{
public:
	Renderer(const std::vector<Vec3>* vertices, const std::vector<unsigned int>* indices)
		: mVertices(*vertices), mIndices(*indices) {};

    void run(GLFWwindow* window, GLuint shaderProgram, GLuint lineShaderProgram, GLuint VAO, GLuint VBO, GLuint EBO, GLuint lineVAO, GLuint lineVBO, int lineVerticesSize);


private:
	std::vector<Vec3> mVertices;
	std::vector<unsigned int> mIndices;
};


inline void Renderer::run(GLFWwindow* window, GLuint shaderProgram, GLuint lineShaderProgram, GLuint VAO, GLuint VBO, GLuint EBO, GLuint lineVAO, GLuint lineVBO, int lineVerticesSize)
{


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glUseProgram(lineShaderProgram);
        glBindVertexArray(lineVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
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