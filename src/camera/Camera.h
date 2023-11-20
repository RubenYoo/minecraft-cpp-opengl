#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <GLFW/glfw3.h>

class Camera
{
public:
	Camera(int width, int height, glm::vec3 initialPosition);
	~Camera();
	
	glm::mat4 CalcCameraMatrix(float fovDeg, float z_near, float z_far);
	void Inputs(GLFWwindow* window);


private:
	unsigned int m_Width;
	unsigned int m_Height;

	glm::vec3 m_Position;
	glm::vec3 m_Orientation;
	glm::vec3 m_Up;

	float m_Speed;
	float m_Sensitivity;

	float m_Yaw;
	float m_Pitch;

	double m_LastMouseX;
	double m_LastMouseY;
};

