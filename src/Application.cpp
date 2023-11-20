#include "Context.h"
#include <iostream>
#include <memory>
#include "renderer/Renderer.h"
#include "camera/Camera.h"
#include "picking/PickingTexture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
    
    context->EnableVSync();
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

            Shader pickShader("assets/shaders/Picking.shader");
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

                pickShader.SetUniformMat4f("u_MVP", mvp);
                pickShader.SetUniform1ui("u_ObjectIndex", i + 1);

                //renderer.DrawBlock(stoneBlock);
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

            vertices.push_back({ {0.0f,  0.0f + 12.0f, 1.0f}, {48.0f / 256.0f, 246.0f / 256.0f}, {0.0f, 0.0f, 0.0f} });
            vertices.push_back({ {32.0f, 0.0f + 12.0f, 1.0f}, {64.0f / 256.0f ,246.0f / 256.0f}, {0.0f, 0.0f, 0.0f} });
            vertices.push_back({ {32.0f, 8.0f + 12.0f, 1.0f}, {64.0f / 256.0f, 250.0f / 256.0f}, {0.0f, 0.0f, 0.0f} });
            vertices.push_back({ {0.0f,  8.0f + 12.0f, 1.0f}, {48.0f / 256.0f, 250.0f / 256.0f}, {0.0f, 0.0f, 0.0f} });
                                                       
            vertices.push_back({ {0.0f + 12.0f, 0.0f,  1.0f}, {54.0f / 256.0f, 240.0f / 256.0f}, {0.0f, 0.0f, 0.0f} });
            vertices.push_back({ {8.0f + 12.0f, 0.0f,  1.0f}, {58.0f / 256.0f, 240.0f / 256.0f}, {0.0f, 0.0f, 0.0f} });
            vertices.push_back({ {8.0f + 12.0f, 32.0f, 1.0f}, {58.0f / 256.0f, 256.0f / 256.0f}, {0.0f, 0.0f, 0.0f} });
            vertices.push_back({ {0.0f + 12.0f, 32.0f, 1.0f}, {54.0f / 256.0f, 256.0f / 256.0f}, {0.0f, 0.0f, 0.0f} });


            std::vector<GLuint> indices = {
                0, 1, 2,
                2, 3, 0,
                4, 5, 6,
                6, 7, 4
            };

            //glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 0.0f));

            glm::mat4 projection = glm::ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT, -1.0f, 1.0f);
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((float)WIDTH/2.0f - 16.0f, (float)HEIGHT/2.0f - 2.0f, 0.0f));
            glm::mat4 mvp = projection *  model /* scale */ ;

            Mesh cursorMesh(vertices, indices);
            cursorMesh.Bind();

   
            Material material("assets/shaders/Cursor.shader", "assets/textures/texture_pack.png");
            material.Bind();
            material.GetShader().SetUniformMat4f("u_MVP", mvp);

            renderer.Draw(cursorMesh.GetVertexArray(), cursorMesh.GetIndexBuffer(), material.GetShader());

        // Render Phase  
            
            glm::mat4 vp = camera.CalcCameraMatrix(45.0f, 0.1f, 100.0f);

            float x = 0.0f;
            float y = 0.0f;
            float z = 0.0f;

            for (size_t i = 0; i < 10; i++)
            {
                bool selected = false;
                glm::vec3 translation(x, y, z);
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
                
               
                if (pixelInfo.ObjectID != 0)
                    if (pixelInfo.ObjectID - 1 == i)
                        selected = true;

                    
                renderer.DrawBlock(stoneBlock, vp, model, selected);
                x++;
            }

            stoneBlock.Unbind();
        }

        
        glfwSwapBuffers(context->GetWindow());
        glfwPollEvents();
    }

    return 0;
}
