#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "GLDebugMessageCallback.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"


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
    window = glfwCreateWindow(600, 600, "Hello World", NULL, NULL);
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

    float positions[] = {
       -0.5f, -0.5f, 0.0f, 0.0f,
        0.5F, -0.5f, 1.0f, 0.0f,
        0.5f,  0.5f, 1.0f, 1.0f,
       -0.5f, 0.5f, 0.0f, 1.0f
    };

    unsigned int indices[6] = {
       0, 1, 2,
       2, 3, 0
    };

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    VertexArray va;
    VertexBufferLayout vbl;
    vbl.Push(GLuint(2), GL_FLOAT, GL_FALSE, 2 * sizeof(float));
    vbl.Push(GLuint(2), GL_FLOAT, GL_FALSE, 2 * sizeof(float));

    VertexBuffer vb(positions, 4 * 4 * sizeof(float), GL_STATIC_DRAW);

    va.AddBuffer(vb, vbl);

    IndexBuffer ib(indices, 6, GL_STATIC_DRAW);

    Shader shader("res/shaders/Basic.shader");
    shader.Bind();

    //shader.SetUniform4f("u_Color", GLfloat(0.8f), GLfloat(0.3f), GLfloat(0.8f), GLfloat(1.0f));

    Texture texture("res/textures/dirt_block.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    va.Bind();

    Renderer renderer;
 
    //GLfloat r = 0.0f;
    //GLfloat increment = 0.05f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();

        //shader.SetUniform4f("u_Color", r, GLfloat(0.3f), GLfloat(0.8f), GLfloat(1.0f));

        renderer.Draw(va, ib, shader);
        //glDrawElements(GL_TRIANGLES, GLint(6), GL_UNSIGNED_INT, nullptr);

        /*
        if (r >= 1.0f)
            increment = -0.05f;
        else if (r <= 0.0f)
            increment = 0.05f;

        r += increment;
        */

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}