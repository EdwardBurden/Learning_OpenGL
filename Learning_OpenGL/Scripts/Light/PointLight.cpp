#include "PointLight.h"

void PointLight::UpdateShader(Shader& shader)
{
	shader.SetUniform("pointLights[0].position", Position);
	shader.SetUniform("pointLights[0].constant", 1.0f);
	shader.SetUniform("pointLights[0].linear", 0.09f);
	shader.SetUniform("pointLights[0].quadratic",0.032f);

	glm::vec3 lightColor = glm::vec3(0.5f, 0.5f, 5.5f);
	glm::vec3 diffuseColor = lightColor * glm::vec3(1.0f);
	glm::vec3 ambientColor = lightColor * glm::vec3(0.1f);
	glm::vec3 specularColor = lightColor * glm::vec3(1.5f);
	shader.SetUniform("pointLights[0].ambient", ambientColor);
	shader.SetUniform("pointLights[0].diffuse", diffuseColor);
	shader.SetUniform("pointLights[0].specular", specularColor);
}
