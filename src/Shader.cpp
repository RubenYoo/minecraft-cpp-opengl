#include "Shader.h"
#include <fstream>
#include <string>
#include <sstream>


Shader::Shader(const std::string& filepath)
	: m_FilePath(filepath), m_RendererID(0)
{
    ShaderProgramSource source = ParseShader(filepath);
    m_RendererID = CreateShader(source.vertexShader, source.fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::ifstream stream(m_FilePath);
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

void Shader::SetUniform1ui(const std::string& name, GLuint value)
{
    glUniform1ui(GetUniformLocation(name), value);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}


GLuint Shader::CompileShader(GLenum type, const std::string& source)
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

        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;

        delete[] message;
        glDeleteShader(id);

        return GLuint(0);
    }

    return id;
}

void Shader::SetUniform1i(const std::string& name, GLint value)
{
    glUniform1i(GetUniformLocation(name), value);
}

GLuint Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
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

void Shader::Bind() const
{
    glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::SetUniform4f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

GLint Shader::GetUniformLocation(const std::string& name)
{
    if (m_UnifromLocationCache.find(name) != m_UnifromLocationCache.end())
        return m_UnifromLocationCache[name];

	GLint location =  glGetUniformLocation(m_RendererID, name.c_str());
    
    if (location == -1)
        std::cout << "Warning: uniform " << name << " doesn't exist!" << std::endl;
    
    m_UnifromLocationCache[name] = location;

    return location;
}
