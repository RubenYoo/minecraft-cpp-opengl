#include "Context.h"
#include <iostream>
#include <memory>
#include "renderer/Renderer.h"
#include "camera/Camera.h"
#include "picking/PickingTexture.h"
#include "mesh/CursorMesh.h"

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

    Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 3.0f));
    Renderer renderer;

    BlockMesh stoneBlock(BlockType::STONE);

    PickingTexture pickingTexture;
    pickingTexture.Init(WIDTH, HEIGHT);

    
    while (!glfwWindowShouldClose(context->GetWindow()))
    {
        camera.Inputs(context->GetWindow());

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
        
            CursorMesh cursor;
            glm::mat4 vp = glm::ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT, -1.0f, 1.0f);
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((float)WIDTH/2.0f - 16.0f, (float)HEIGHT/2.0f - 2.0f, 0.0f));
            renderer.DrawCursor(cursor, vp, model);

        // Render Phase  
            
            vp = camera.CalcCameraMatrix(45.0f, 0.1f, 100.0f);

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
