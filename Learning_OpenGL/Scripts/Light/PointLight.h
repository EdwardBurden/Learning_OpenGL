#pragma once
#include "Light.h"
class PointLight : public Light
{
	using Light::Light;
public:
	void UpdateShader(Shader& shader) override;
};

