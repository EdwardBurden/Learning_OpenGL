#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
static const float MaxPitch = 89;

class Camera
{
public:
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;

	Camera();
	void UpdateCamera(float deltaTime);
	void UpdateCameraPosition(glm::vec2 inputVector);
	void UpdateCameraLook(float yaw, float pitch);

private:
	glm::vec3 CameraPos;
	glm::vec3 CameraUp;
	glm::vec3 CameraFront;
	glm::vec3 CameraRight;
	glm::vec3 CameraPosChange;
	float Speed;
	float YawValue;
	float PitchValue;
};

