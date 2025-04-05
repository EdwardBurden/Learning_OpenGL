#include "Camera.h"

Camera::Camera()
{
	CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	CameraRight = glm::vec3(1.0f, 0.0f, 0.0f);
	CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	YawValue = -90.0f;
	PitchValue = 0.0f;
	ProjectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 500.0f); // 
	Speed = 2.5f;
}

void Camera::UpdateCamera(float deltaTime)
{
	CameraPos += CameraPosChange * deltaTime * Speed;
	ViewMatrix = glm::lookAt(CameraPos, CameraPos + CameraFront, CameraUp);
	CameraPosChange = glm::vec3(0, 0, 0);
}

void Camera::UpdateCameraPosition(glm::vec2 inputVector)
{
	glm::vec3 movement = glm::vec3(inputVector.x, 0, inputVector.y);
	CameraPosChange = (movement.x * CameraRight) + (movement.z * CameraFront);
}

void Camera::UpdateCameraLook(float yaw, float pitch)
{
	YawValue += yaw;
	PitchValue += pitch;

	if (PitchValue > MaxPitch)
		PitchValue = MaxPitch;
	if (PitchValue < -MaxPitch)
		PitchValue = -MaxPitch;

	glm::vec3 direction;
	direction.x = cos(glm::radians(YawValue)) * cos(glm::radians(PitchValue));
	direction.y = sin(glm::radians(PitchValue));
	direction.z = sin(glm::radians(YawValue)) * cos(glm::radians(PitchValue));
	CameraFront = glm::normalize(direction);;
	CameraRight = glm::normalize(glm::cross(CameraUp, CameraFront));
}
