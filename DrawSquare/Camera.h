#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Camera
{
public:
	 Camera(const glm::vec3& Loc,
			float Yaw,
			float Pitch,
			float MoveSpeed,
			float RotateSpeed,
			struct GLFWwindow* Window,
			float FOV,
			float FarClipPlane,
			float NearClipPlane
		);

	 Camera();

	 void SetWindow(GLFWwindow* window) { m_Window = window; }
	 void Update(float DeltaTime);
	 glm::mat4 GetViewMatrix();
private: //Variables
	glm::vec3 m_CameraLocation;
	float m_Yaw;					//looking right and left
	float m_Pitch;					//looking up and down
	float m_MoveSpeed;
	float m_RotateSpeed;
	struct GLFWwindow* m_Window;
	float m_FOV;
	float m_FarClipPlane;
	float m_NearClipPlane;

	glm::vec3 m_ForwardVec;
	glm::vec3 m_RightVec;
	glm::vec3 m_UpVec;

private: //Functions
	void CalculateCameraDirs();
};
