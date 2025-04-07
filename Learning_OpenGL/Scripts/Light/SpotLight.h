#pragma once
#include "Light.h"
class SpotLight : public Light
{
	using Light::Light;
public:
	void UpdateShader(Shader& shader) override;
};

