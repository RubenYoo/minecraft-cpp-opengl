#include "Context.h"
#include <iostream>
#include <memory>
#include "Renderer.h"
#include "Camera.h"
#include "PickingTexture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "tests/TestClearColor.h"

constexpr auto WIDTH = 1920;
constexpr auto HEIGHT = 1080;

int main()
{
    std::unique_ptr<Context> context = nullptr;

    try
    {
        context = std::make_unique<Context>(WIDTH, HEIGHT, "Minecraft");
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what();
    }
    

    BlockMesh stoneBlock(BlockType::STONE);
    BlockMesh grassBlock(BlockType::GRASS);
    BlockMesh dirtBlock(BlockType::DIRT);

    Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 3.0f));
    Renderer renderer;

    PickingTexture pickingTexture;
    pickingTexture.Init(WIDTH, HEIGHT);

    
    while (!glfwWindowShouldClose(context->GetWindow()))
    {
        camera.Inputs(context->GetWindow());

        /*
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        */

        // Picking Phase
        {
            pickingTexture.EnableWriting();
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            renderer.Clear();

            glm::mat4 vp = camera.CalcCameraMatrix(45.0f, 0.1f, 100.0f);

            Shader pickShader("res/shaders/Picking.shader");
            pickShader.Bind();

            float x = 0.0f;
            float y = 0.0f;
            float z = 0.0f;


            stoneBlock.BindMesh();

            for (GLuint i = 0; i < 10; i++)
            {
                glm::vec3 translation(x, y, z);

                glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
                glm::mat4 mvp = vp * model;

                pickShader.SetUniformMat4f("gWVP", mvp);
                pickShader.SetUniform1ui("gObjectIndex", i + 1);

                renderer.DrawBlock(stoneBlock);
                x++;
            }


            stoneBlock.Unbind();
            pickShader.Unbind();
            pickingTexture.DisableWriting();

        }

        // Checking Phase
        {
            PickingTexture::PixelInfo pixelInfo = pickingTexture.ReadPixel(WIDTH / 2, HEIGHT / 2);
            //pixelInfo.Print();


            glClearColor(0.729f, 0.976f, 1.0f, 1.0f);
            renderer.Clear();
        

        // Cursor
        
            float texPos = 1.0f / 16.0f;
            std::vector<Vertex> vertices;

            vertices.push_back({ {935.0f, 535.0f, 1.0f}, {54.0f / 256.0f, texPos * 15}, {0.0f, 0.0f, 0.0f} });
            vertices.push_back({ {985.0f, 535.0f, 1.0f}, {58.0f / 256.0f ,texPos * 15}, {0.0f, 0.0f, 0.0f}});
            vertices.push_back({ {985.0f, 545.0f, 1.0f}, {58.0f / 256.0f, texPos * 16}, {0.0f, 0.0f, 0.0f} });
            vertices.push_back({ {935.0f, 545.0f, 1.0f}, {54.0f / 256.0f, texPos * 16}, {0.0f, 0.0f, 0.0f} });

            vertices.push_back({ {955.0f, 515.0f, 1.0f}, {texPos * 3, 246.0f / 256.0f}, {0.0f, 0.0f, 0.0f} });
            vertices.push_back({ {965.0f, 515.0f, 1.0f}, {texPos * 4, 246.0f / 256.0f}, {0.0f, 0.0f, 0.0f} });
            vertices.push_back({ {965.0f, 565.0f, 1.0f}, {texPos * 4, 250.0f / 256.0f}, {0.0f, 0.0f, 0.0f} });
            vertices.push_back({ {955.0f, 565.0f, 1.0f}, {texPos * 3, 250.0f / 256.0f}, {0.0f, 0.0f, 0.0f} });


            std::vector<GLuint> indices = {
                0, 1, 2,
                2, 3, 0,
                4, 5, 6,
                6, 7, 4
            };

            //glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 0.0f));

            glm::mat4 projection = glm::ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT, -1.0f, 1.0f);
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 15.0f, 0.0f));
            glm::mat4 mvp = projection *  model /* scale*/;

            Mesh cursorMesh(vertices, indices);
            cursorMesh.Bind();

   
            Material material("res/shaders/Basic.shader", "res/textures/texture_pack.png");
            material.Bind();
            material.GetShader().SetUniformMat4f("u_MVP", mvp);

            renderer.Draw(cursorMesh.GetVertexArray(), cursorMesh.GetIndexBuffer(), material.GetShader());

        // Render Phase  
            
            stoneBlock.Bind();
            glm::mat4 vp = camera.CalcCameraMatrix(45.0f, 0.1f, 100.0f);

            float x = 0.0f;
            float y = 0.0f;
            float z = 0.0f;

            for (size_t i = 0; i < 10; i++)
            {
                glm::vec3 translation(x, y, z);

                glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
                glm::mat4 mvp = vp * model;
                stoneBlock.GetMaterial().GetShader().SetUniformMat4f("u_MVP", mvp);
                stoneBlock.GetMaterial().GetShader().SetUniform1f("u_BorderThickness", 0.0);
                stoneBlock.GetMaterial().GetShader().SetUniform3f("u_BorderColor", 1.0, 1.0, 1.0);
               
                if (pixelInfo.ObjectID != 0)
                    if (pixelInfo.ObjectID - 1 == i)
                        stoneBlock.GetMaterial().GetShader().SetUniform1f("u_BorderThickness", 1.0);

                    
                renderer.DrawBlock(stoneBlock);
                x++;
            }

            /*
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

            y = 30.0f;
            glm::vec3 translation(x, y, z);

            glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
            glm::mat4 mvp = vp * model;
            grassBlock.GetMaterial().GetShader().SetUniformMat4f("u_MVP", mvp);
            renderer.DrawBlock(grassBlock);

            dirtBlock.Unbind();
            grassBlock.Unbind();
            */

            stoneBlock.Unbind();
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

        glfwSwapBuffers(context->GetWindow());
        glfwPollEvents();
    }

    return 0;
}
