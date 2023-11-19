#include "Camera.h"
#include <iostream>

Camera::Camera(int width, int height, glm::vec3 initialPosition)
    : m_Width(width), m_Height(height), m_Speed(0.1f), m_Sensitivity(0.1f), m_Yaw(-90.0f), m_Pitch(0.0f),
      m_LastMouseX(m_Width / 2), m_LastMouseY(m_Height / 2)
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
    glm::mat4 proj = glm::perspective(glm::radians(fovDeg), float(m_Width) / float(m_Height), z_near, z_far);

    glm::mat4 view = glm::lookAt(m_Position, m_Orientation + m_Position, m_Up);
    
    return proj * view;
}

void Camera::Inputs(GLFWwindow* window)
{
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Get the current mouse position
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    // Calculate the change in mouse position since the last frame
    double deltaX = mouseX - m_LastMouseX;
    double deltaY = mouseY - m_LastMouseY;

    // Update the last mouse position for the next frame
    m_LastMouseX = mouseX;
    m_LastMouseY = mouseY;

    deltaX *= m_Sensitivity;
    deltaY *= m_Sensitivity;

    m_Yaw += deltaX;
    m_Pitch += deltaY;

    if (m_Pitch > 89.0f)
        m_Pitch = 89.0f;
    if (m_Pitch < -89.0f)
        m_Pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    direction.y = -sin(glm::radians(m_Pitch));
    direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Orientation = glm::normalize(direction);

    // Handles key inputs
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // Z
    {
        m_Position += m_Speed * glm::normalize(glm::vec3(m_Orientation.x, 0.0f, m_Orientation.z));
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // Q
    {
        m_Position -= m_Speed * glm::normalize(glm::cross((m_Orientation), m_Up));
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // S
    {
        m_Position -= m_Speed * glm::normalize(glm::vec3(m_Orientation.x, 0.0f, m_Orientation.z));
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // D
    {
        m_Position -= m_Speed * glm::normalize(glm::cross(m_Up, m_Orientation));
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        m_Position.y += m_Speed;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        m_Position.y -= m_Speed;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        m_Speed = 0.4;
    }
    else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
    {
        m_Speed = 0.1;
    }

}
