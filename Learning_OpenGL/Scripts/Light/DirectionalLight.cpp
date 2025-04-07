#include "DirectionalLight.h"

void DirectionalLight::UpdateShader(Shader& shader)
{
	glm::vec3 direction = glm::normalize( glm::vec3(0.3f, -1.0f, -0.5f));
	glm::vec3 lightColor = glm::vec3(1.5f, 0.5f, 0.5f);
	glm::vec3 diffuseColor = lightColor * glm::vec3(1.0f);
	glm::vec3 ambientColor = lightColor * glm::vec3(0.1f);
	glm::vec3 specularColor = lightColor * glm::vec3(1.5f);

	shader.SetUniform("directionLight.direction", Forward);
	shader.SetUniform("directionLight.ambient", ambientColor);
	shader.SetUniform("directionLight.diffuse", diffuseColor);
	shader.SetUniform("directionLight.specular", specularColor);
	shader.SetUniform("color", lightColor);
}
