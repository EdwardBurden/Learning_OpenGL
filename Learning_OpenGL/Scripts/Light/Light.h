#pragma once
#include "../Shader.h"
#include "../SceneObject.h"

class Light : public SceneObject
{
	using SceneObject::SceneObject;
	virtual void UpdateShader(Shader& shader) = 0;
};

