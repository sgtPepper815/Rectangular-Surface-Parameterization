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

	Renderer(const std::vector<Vec3>* _vertices, const std::vector<unsigned int>* _indices)
		: mVertices(*_vertices), mIndices(*_indices) {};

    void run(GLFWwindow* window, 
        GLuint shaderProgram, 
        GLuint blackShaderProgram,
        GLuint lineShaderProgram, 
        GLuint VAO, 
        GLuint VBO, 
        GLuint EBO, 
        GLuint lineVAO, 
        GLuint lineVBO, 
        GLsizei lineVerticesSize,
        Camera* camera);


private:
	std::vector<Vec3> mVertices;
	std::vector<unsigned int> mIndices;
};


inline void Renderer::run(GLFWwindow* window, 
    GLuint shaderProgram, 
    GLuint blackShaderProgram, 
    GLuint lineShaderProgram, 
    GLuint VAO, 
    GLuint VBO, 
    GLuint EBO, 
    GLuint lineVAO, 
    GLuint lineVBO, 
    GLsizei lineVerticesSize, 
    Camera* camera)
{
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // model matrix
        glm::mat4 model = glm::mat4(1.0f);

        // view matrix
        glm::vec3 cameraPosition = camera->getCameraPosition();
        glm::mat4 view = camera->getViewMatrix(cameraPosition);

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

        // START MESH
        glUseProgram(shaderProgram);

        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(1.0f, 1.0f);

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
        glDisable(GL_POLYGON_OFFSET_FILL);
        // END MESH

        // START BLACK LINES
        glUseProgram(blackShaderProgram);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glUniformMatrix4fv(
            glGetUniformLocation(blackShaderProgram, "model"),
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );

        glUniformMatrix4fv(
            glGetUniformLocation(blackShaderProgram, "view"),
            1,
            GL_FALSE,
            glm::value_ptr(view)
        );

        glUniformMatrix4fv(
            glGetUniformLocation(blackShaderProgram, "projection"),
            1,
            GL_FALSE,
            glm::value_ptr(projection)
        );
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        // 3. Zurücksetzen
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        // END BLACK LINES

        // BEGIN NORMALS AND TANGENTIALS
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

        for (int i = 0; i < lineVerticesSize; i += 6)
        {
            // normal - blue
            glUniform3f(
                glGetUniformLocation(lineShaderProgram, "lineColor"),
                0.1f, 0.1f, 1.0f
            );
            glDrawArrays(GL_LINES, i, 2);

            // t1 - red
            glUniform3f(
                glGetUniformLocation(lineShaderProgram, "lineColor"),
                1.0f, 0.1f, 0.1f
            );
            glDrawArrays(GL_LINES, i+2, 2);

            // t2 - green
            glUniform3f(
                glGetUniformLocation(lineShaderProgram, "lineColor"),
                0.0f, 1.0f, 0.1f
            );
            glDrawArrays(GL_LINES, i+4, 2);
        }

        // END NORMALS

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