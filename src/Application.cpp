#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "GLDebugMessageCallback.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

struct ShaderProgramSource {
    std::string vertexShader;
    std::string fragmentShader;
};

static ShaderProgramSource ParseShader(const std::string& pathFile)
{
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::ifstream stream(pathFile);
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
            else
                type = ShaderType::NONE;
        }
        else
        {
            if (type != ShaderType::NONE)
                ss[int(type)] << line << '\n';
        }  
    }

    return ShaderProgramSource{ ss[0].str(), ss[1].str() };
}


static GLuint CompileShader(GLenum type, const std::string& source)
{
    GLuint id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, GLsizei(1), &src, nullptr);
    glCompileShader(id);

    //Error handling

    GLint result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        GLint length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = new char[length];

        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex": "fragment") << " shader!" << std::endl;

        delete[] message;
        glDeleteShader(id);

        return GLuint(0);
    }

    return id;
}

static GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    GLuint program = glCreateProgram();
    GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);

    glDetachShader(program, vs);
    glDetachShader(program, fs);

    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

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

    GLuint vao;
    glGenVertexArrays(GLsizei(1), &vao);
    glBindVertexArray(vao);

    VertexBuffer vb(positions, 4 * 2 * sizeof(float), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(GLuint(0), GLuint(2), GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    IndexBuffer ib(indices, 6, GL_STATIC_DRAW);

    ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
    GLuint shader = CreateShader(source.vertexShader, source.fragmentShader);
    glUseProgram(shader);

    GLint location = glGetUniformLocation(shader, "u_Color");
    _ASSERT(location != -1);

    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glUseProgram(shader);
    glBindVertexArray(vao);
    //ib.Bind();


    GLfloat r = 0.0f;
    GLfloat increment = 0.05f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUniform4f(location, r, GLfloat(0.3f), GLfloat(0.8f), GLfloat(1.0f));

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

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}