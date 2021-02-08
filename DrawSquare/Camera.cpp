#include <Camera.h>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
Camera::Camera(const glm::vec3& Loc, float Yaw,float Pitch, 
	float MoveSpeed,float RotateSpeed, struct GLFWwindow* Window,
	float FOV,float FarClipPlane,float NearClipPlane)
	:m_CameraLocation(Loc),m_Yaw(Yaw),m_Pitch(Pitch),m_MoveSpeed(MoveSpeed),m_RotateSpeed(RotateSpeed),m_Window(Window),
	m_FOV(FOV),m_FarClipPlane(FarClipPlane),
	m_NearClipPlane(NearClipPlane),m_ForwardVec(0.f,0.f,0.f)
{
	CalculateCameraDirs();
}

Camera::Camera()
	: Camera(glm::vec3(0.f, 0.f, -3.f), -90.0f, 0.f, 10.f , 20.f ,nullptr, 45.f, 0.f, 1000.f) {}


void Camera::CalculateCameraDirs()
{
	//Calculation of the forward vector based on the yaw and pitch values
	m_ForwardVec.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_ForwardVec.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_ForwardVec.y = sin(glm::radians(m_Pitch));

	m_ForwardVec = glm::normalize(m_ForwardVec);

	//Calculation of the right vector using cross
	m_RightVec = glm::cross(m_ForwardVec, glm::vec3(0.f, 1.f, 0.f));
	m_UpVec = glm::cross(m_RightVec, m_ForwardVec);
}

void Camera::Update(float DeltaTime,bool &cursorLocked)
{
	if (m_Window)
	{
		if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
			m_CameraLocation += m_ForwardVec * m_MoveSpeed * DeltaTime;
		if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
			m_CameraLocation -= m_ForwardVec * m_MoveSpeed * DeltaTime;
		if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
			m_CameraLocation -= m_RightVec * m_MoveSpeed * DeltaTime;
		if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
			m_CameraLocation += m_RightVec * m_MoveSpeed * DeltaTime;
		
		if (glfwGetKey(m_Window, GLFW_KEY_E) == GLFW_PRESS && cursorLocked)
		{
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			cursorLocked = false;
		}
		if (glfwGetKey(m_Window, GLFW_KEY_R) == GLFW_PRESS && !cursorLocked)
		{
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			cursorLocked = true;
		}
		
	}
	//std::cout << "CameraLocation: " << m_ForwardVec.x << ", "<< m_ForwardVec.y << ", " << m_ForwardVec.z << std::endl;
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(m_CameraLocation, m_CameraLocation + m_ForwardVec, m_UpVec);
}

void Camera::CusorMoved(double xPos, double yPos)
{
	static double CursorPreviousPosX = 0.0;
	static double CursorPreviousPosY = 0.0;

	CursorPreviousPosX = xPos;
	CursorPreviousPosY = yPos;

	double xOffset = xPos - CursorPreviousPosX;
	double yOffset = yPos - CursorPreviousPosY;

	m_Yaw += xOffset * m_RotateSpeed;
	m_Pitch -= yOffset * m_RotateSpeed;

	//lock the value of pitch between -89 and 89
	m_Pitch = m_Pitch > 89 ? 89 : m_Pitch;
	m_Pitch = m_Pitch < -89 ? -98 : m_Pitch;

	CalculateCameraDirs();
}
