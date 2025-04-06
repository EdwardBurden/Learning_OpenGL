#pragma once
#include <glm.hpp>

class SceneObject
{
public:
	SceneObject(glm::vec3 position, glm::vec3 forward);
	virtual void Update(float deltaTime);
	glm::vec3 Position;
	glm::vec3 Forward;
};

