#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 initialPosition)
	: m_Width(width), m_Height(height), m_Speed(0.1f), m_Sensitivity(100.0f), m_Yaw(-90.0f), m_Pitch(0.0f)
{
	m_Position = initialPosition;
	m_Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
}

Camera::~Camera()
{
}

glm::mat4 Camera::CalcCameraMatrix(float fovDeg, float z_near, float z_far)
{
	glm::mat4 proj = glm::perspective(glm::radians(fovDeg), float(m_Width / m_Height), z_near, z_far);

	glm::mat4 view = glm::lookAt(m_Position, m_Orientation, m_Up);

	return proj * view;
}

void Camera::Inputs(GLFWwindow* window)
{
	static bool isCameraMovementEnabled = true; 

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		isCameraMovementEnabled = !isCameraMovementEnabled;

	if (!isCameraMovementEnabled)
		return;


	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	static double lastMouseX = mouseX;
	static double lastMouseY = mouseY;
	double deltaX = mouseX - lastMouseX;
	double deltaY = mouseY - lastMouseY;

	lastMouseX = mouseX;
	lastMouseY = mouseY;

	float sensitivity = 0.1f;
	deltaX *= sensitivity;
	deltaY *= sensitivity;

	m_Yaw += deltaX;
	m_Pitch -= deltaY;

	glm::vec3 front;
	front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	front.y = sin(glm::radians(m_Pitch));
	front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Orientation = glm::normalize(front);

	// Handles key inputs

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_Position += m_Speed * m_Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_Position -= m_Speed * m_Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_Position -= m_Speed * m_Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_Position += m_Speed * m_Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		m_Position += m_Speed * m_Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		m_Position -= m_Speed * m_Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		m_Speed = 0.4f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		m_Speed = 0.1f;
	}
}
