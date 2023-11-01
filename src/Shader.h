#pragma once
#include <iostream>
#include <GL/glew.h>
#include <unordered_map>

struct ShaderProgramSource {
	std::string vertexShader;
	std::string fragmentShader;
};

class Shader
{
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform4f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

private:
	GLuint m_RendererID;
	std::string m_FilePath;
	std::unordered_map<std::string, GLint> m_UnifromLocationCache;

	GLint GetUniformLocation(const std::string& name);
	GLuint CompileShader(GLenum type, const std::string& source);
	GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	ShaderProgramSource ParseShader(const std::string& filepath);
};
