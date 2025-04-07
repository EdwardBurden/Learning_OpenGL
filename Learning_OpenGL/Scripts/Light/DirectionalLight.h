#pragma once
#include "Light.h"
class DirectionalLight : public Light
{
	using Light::Light;
public:
	void UpdateShader(Shader& shader) override;
};