#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "GLDebugMessageCallback.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error: Glew was not init" << std::endl;

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(GLDebugMessageCallback, nullptr);

    std::cout << glGetString(GL_VERSION) << std::endl;

    float positions[8] = {
       -0.5f, -0.5f,
        0.5F, -0.5f,
        0.5f,  0.5f,
       -0.5f, 0.5f
    };

    unsigned int indices[6] = {
       0, 1, 2,
       2, 3, 0
    };

    VertexArray vao;
    VertexBufferLayout vbl;
    vbl.Push(GLuint(2), GL_FLOAT, GL_FALSE, 2 * sizeof(float));

    VertexBuffer vb(positions, 4 * 2 * sizeof(float), GL_STATIC_DRAW);

    vao.AddBuffer(vb, vbl);

    IndexBuffer ib(indices, 6, GL_STATIC_DRAW);

    Shader shader("res/shaders/Basic.shader");
    shader.Bind();

    shader.SetUniform4f("u_Color", GLfloat(0.8f), GLfloat(0.3f), GLfloat(0.8f), GLfloat(1.0f));
    vao.Bind();
 
    GLfloat r = 0.0f;
    GLfloat increment = 0.05f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        shader.SetUniform4f("u_Color", r, GLfloat(0.3f), GLfloat(0.8f), GLfloat(1.0f));

        glDrawElements(GL_TRIANGLES, GLint(6), GL_UNSIGNED_INT, nullptr);

        if (r >= 1.0f)
            increment = -0.05f;
        else if (r <= 0.0f)
            increment = 0.05f;

        r += increment;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}