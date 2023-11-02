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

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


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
    window = glfwCreateWindow(960, 540, "Minecraft", NULL, NULL);
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
       100.0f, 100.0f, 0.0f, 0.0f,
       200.0f, 100.0f, 1.0f, 0.0f,
       200.0f, 200.0f, 1.0f, 1.0f,
       100.0f, 200.0f, 0.0f, 1.0f
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

    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f, 0.0f, 0.0f));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200.0f, 200.0f, 0.0f));

    glm::mat4 mvp = proj * view * model;

    Shader shader("res/shaders/Basic.shader");
    shader.Bind();


    Texture texture("res/textures/dirt_block.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);
    shader.SetUniformMat4f("u_MVP", mvp);

    va.Bind();

    Renderer renderer;
 

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();

        renderer.Draw(va, ib, shader);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}