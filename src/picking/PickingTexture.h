#pragma once

#include <GL/glew.h>
#include <iostream>

class PickingTexture
{
public:
    PickingTexture();

    ~PickingTexture();

    void Init(unsigned int windowWidth, unsigned int windowHeight);

    void EnableWriting();

    void DisableWriting();

    struct PixelInfo {
        GLuint ObjectID = 0;
        GLuint DrawID = 0;
        GLuint PrimID = 0;

        void Print()
        {
            std::cout << "Object " << ObjectID << std::endl;
        }
    };

    PixelInfo ReadPixel(unsigned int x, unsigned int y);

private:
    GLuint m_Fbo = 0;
    GLuint m_PickingTexture = 0;
    GLuint m_DepthTexture = 0;

};