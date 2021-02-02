#pragma once
#include <glm/glm.hpp>
class Camera
{
public:
	Camera(const float WindowWidth,const float WindowHeight,float CameraMovementSpeed,unsigned int mainProgram);
	glm::mat4 ProjectionMatrix;
	glm::vec3 CameraLocation;
	int ProjectMatrixLoc;
	float CameraMovementSpeed;
	glm::mat4 viewMatrix;
	int ViewMatrixLoc;
private:
	float WindowWidth;
	float WindowHeight;
	unsigned int Program;
	float AspectRatio;
};
