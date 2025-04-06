#include "Camera.h"

Camera::Camera() : SceneObject{ glm::vec3(0.0) , glm::vec3(0.0) }
{
	Position = glm::vec3(0.0f, 0.0f, 7.0f);
	CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	YawValue = -90.0f;
	PitchValue = 0.0f;
	ProjectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 500.0f); // 
	Speed = 2.5f;
	UpdateCameraLook(0, 0);
}

void  Camera::Update(float deltaTime)
{
	Position += CameraPosChange * deltaTime * Speed;
	ViewMatrix = glm::lookAt(Position, Position + Forward, CameraUp);
	CameraPosChange = glm::vec3(0, 0, 0);
}

void Camera::UpdateCameraPosition(glm::vec2 inputVector)
{
	glm::vec3 movement = glm::vec3(inputVector.x, 0, inputVector.y);
	CameraPosChange = (movement.x * CameraRight) + (movement.z * Forward);
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
	Forward = glm::normalize(direction);;
	CameraRight = glm::normalize(glm::cross(CameraUp, Forward));
}
