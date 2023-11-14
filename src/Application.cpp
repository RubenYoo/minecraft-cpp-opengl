#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "openGL/GLDebugMessageCallback.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include "Mesh.h"
#include "BlockMesh.h"

#include "Camera.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "tests/TestClearColor.h"

#define width 1600
#define height 800

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

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glFrontFace(GL_CW);
    //glCullFace(GL_FRONT);


    BlockMesh stoneBlock(BlockType::STONE);
    BlockMesh grassBlock(BlockType::GRASS);
    BlockMesh dirtBlock(BlockType::DIRT);

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 3.0f));
 
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


    GLfloat m_ClearColor[] = { 0.729f, 0.976f, 1.0f, 1.0f };


    while (!glfwWindowShouldClose(window))
    {
        glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
        renderer.Clear();
        camera.Inputs(window);

        /*
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        */

        {
            stoneBlock.Bind();
            glm::mat4 vp = camera.CalcCameraMatrix(45.0f, 0.1f, 100.0f);

            float x = 0.0f;
            float y = 0.0f;
            float z = 0.0f;

            for (size_t i = 0; i < 10; i++)
            {
                z = 0.0f;

                for (size_t i = 0; i < 10; i++)
                {
                    x = 0.0f;

                    for (size_t i = 0; i < 10; i++)
                    {
                        glm::vec3 translation(x, y, z);

                        glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
                        glm::mat4 mvp = vp * model;
                        stoneBlock.GetMaterial().GetShader().SetUniformMat4f("u_MVP", mvp);
                        renderer.DrawBlock(stoneBlock);
                        x++;
                    }
                    z++;
                }
                y++;
            }

            dirtBlock.Bind();

            for (size_t i = 0; i < 3; i++)
            {
                z = 0.0f;

                for (size_t i = 0; i < 10; i++)
                {
                    x = 0.0f;

                    for (size_t i = 0; i < 10; i++)
                    {
                        glm::vec3 translation(x, y, z);

                        glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
                        glm::mat4 mvp = vp * model;
                        dirtBlock.GetMaterial().GetShader().SetUniformMat4f("u_MVP", mvp);
                        renderer.DrawBlock(dirtBlock);
                        x++;
                    }
                    z++;
                }
                y++;
            }

            grassBlock.Bind();

            for (size_t i = 0; i < 1; i++)
            {
                z = 0.0f;

                for (size_t i = 0; i < 10; i++)
                {
                    x = 0.0f;

                    for (size_t i = 0; i < 10; i++)
                    {
                        glm::vec3 translation(x, y, z);

                        glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
                        glm::mat4 mvp = vp * model;
                        grassBlock.GetMaterial().GetShader().SetUniformMat4f("u_MVP", mvp);
                        renderer.DrawBlock(grassBlock);
                        x++;
                    }
                    z++;
                }
                y++;
            }

        }

        /*
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
        */

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}
