#pragma once
#include <glm/glm.hpp>
class Camera
{
public:
	Camera(const float WindowWidth,const float WindowHeight,float CameraMovementSpeed,unsigned int mainProgram);


public: //Variables
	glm::mat4 ProjectionMatrix;
	int ProjectMatrixLoc;
	float CameraMovementSpeed;
	glm::mat4 viewMatrix;
	int ViewMatrixLoc;
private: //Variables
	glm::vec3 CameraLocation;
	float WindowWidth;
	float WindowHeight;
	unsigned int Program;
	float AspectRatio;
};
