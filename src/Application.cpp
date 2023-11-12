#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "openGL/GLDebugMessageCallback.h"
#include "openGL/VertexBuffer.h"
#include "openGL/IndexBuffer.h"
#include "openGL/VertexArray.h"
#include "openGL/VertexBufferLayout.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"

#include "Camera.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "tests/TestClearColor.h"

#define width 1600.0f
#define height 800.0f

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
    window = glfwCreateWindow(width, height, "Minecraft", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error: Glew was not init" << std::endl;

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(GLDebugMessageCallback, nullptr);

    std::cout << glGetString(GL_VERSION) << std::endl;

    float texPos = 1.0f / 16.0f;

    float positions[] = {
       -0.5f, -0.5f, 0.5f, texPos, texPos * 15,
        0.5f, -0.5f, 0.5f, texPos * 2, texPos * 15,
        0.5f,  0.5f, 0.5f, texPos * 2, texPos * 16,
       -0.5f,  0.5f, 0.5f, texPos, texPos * 16,

       -0.5f, -0.5f, -0.5f, texPos * 2, texPos * 15,
        0.5f, -0.5f, -0.5f, texPos, texPos * 15,
        0.5f,  0.5f, -0.5f, texPos, texPos * 16,
       -0.5f,  0.5f, -0.5f, texPos * 2, texPos * 16,

       -0.5f,  0.5f, 0.5f, texPos * 2, texPos * 15,
        0.5f,  0.5f, 0.5f, texPos * 3, texPos * 15,
        0.5f,  0.5f, -0.5f, texPos * 3, texPos * 16,
       -0.5f,  0.5f, -0.5f, texPos * 2, texPos * 16,

       -0.5f, -0.5f, 0.5f, 0, texPos * 15,
        0.5f, -0.5f, 0.5f, texPos, texPos * 15,
        0.5f, -0.5f, -0.5f, texPos, texPos * 16,
       -0.5f,  -0.5f, -0.5f, 0, texPos * 16
    };

    unsigned int indices[] = {
       0, 1, 2,
       2, 3, 0,
       1, 5, 6,
       6, 2, 1,
       5, 4, 7,
       7, 6, 5,
       4, 0, 3,
       3, 7, 4,
       8, 9, 10,
       10, 11, 8,
       12, 13, 14,
       14, 15, 12
    };

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glFrontFace(GL_CW);
    //glCullFace(GL_FRONT);

    VertexArray va;
    VertexBufferLayout vbl;
    vbl.Push(GLuint(3), GL_FLOAT, GL_FALSE, 3 * sizeof(float));
    vbl.Push(GLuint(2), GL_FLOAT, GL_FALSE, 2 * sizeof(float));

    VertexBuffer vb(positions, sizeof(positions), GL_STATIC_DRAW);

    va.AddBuffer(vb, vbl);

    IndexBuffer ib(indices, sizeof(indices) / sizeof(unsigned int), GL_STATIC_DRAW);

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 3.0f));

    Shader shader("res/shaders/Basic.shader");
    shader.Bind();

    Texture texture("res/textures/texture_pack.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);
    //shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.2f, 1.0f);

    va.Bind();

    Renderer renderer;

    const char* glsl_version = "#version 150";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    glm::vec3 translationA(0.0f, 0.0f, 0.0f);
    glm::vec3 translationB(1.0f, 0.0f, 0.0f);
    GLfloat m_ClearColor[] = { 0.729f, 0.976f, 1.0f, 1.0f };

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
        renderer.Clear();
        camera.Inputs(window);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
            glm::mat4 mvp = camera.CalcCameraMatrix(45.0f, 0.1f, 100.0f) * model;
            shader.SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(va, ib, shader);
        }

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
            glm::mat4 mvp = camera.CalcCameraMatrix(45.0f, 0.1f, 100.0f) * model;
            shader.SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(va, ib, shader);
        }

        {
            ImGui::Begin("Modifications");

            ImGui::Text("Translation for first block:");
            ImGui::PushItemWidth(100);
            ImGui::SliderFloat("X##TranslationA", &translationA.x, -5.0f, 5.0f);
            ImGui::SameLine();
            ImGui::SliderFloat("Y##TranslationA", &translationA.y, -5.0f, 5.0f);
            ImGui::SameLine();
            ImGui::SliderFloat("Z##TranslationA", &translationA.z, -5.0f, 5.0f);
            ImGui::PopItemWidth();

            ImGui::Separator();

            ImGui::Text("Translation for second block:");
            ImGui::PushItemWidth(100);
            ImGui::SliderFloat("X##TranslationB", &translationB.x, -2.0f, 2.0f);
            ImGui::SameLine();
            ImGui::SliderFloat("Y##TranslationB", &translationB.y, -2.0f, 2.0f);
            ImGui::SameLine();
            ImGui::SliderFloat("Z##TranslationB", &translationB.z, -2.0f, 2.0f);
            ImGui::PopItemWidth();

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}
