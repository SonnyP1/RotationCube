#include "Camera.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <fstream>

Camera::Camera(const float windowWidth, const float windowHeight, float cameraMovementSpeed, unsigned int mainProgram)
	:CameraMovementSpeed(cameraMovementSpeed), Program(mainProgram), AspectRatio(windowWidth/windowHeight)
{
	ProjectMatrixLoc = glGetUniformLocation(Program, "ProjectMatrix");
	ProjectionMatrix = glm::perspective(glm::radians(45.f), AspectRatio, 0.01f, 1000.f);
	CameraLocation = glm::vec3(0.f, 0.f, 0.f);

	viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3));
	ViewMatrixLoc = glGetUniformLocation(Program, "ViewMatrix");
}