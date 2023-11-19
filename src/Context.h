#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Context
{
public:
	Context(unsigned int width, unsigned int height, std::string name);
	~Context();

	void CreateGlfwContext();
	void CreateGlewContext();
	void CreateImGuiContext();

	void EnableVSync();

	inline GLFWwindow* GetWindow() const { return m_Window; }

private:
	GLFWwindow* m_Window;
	unsigned int m_Width;
	unsigned int m_Height;
	std::string m_Name;
};
