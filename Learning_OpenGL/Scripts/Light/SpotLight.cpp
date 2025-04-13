#include "SpotLight.h"

void SpotLight::UpdateShader(Shader& shader)
{
	glm::vec3 lightColor = glm::vec3(3.0f);
	glm::vec3 diffuseColor = lightColor * glm::vec3(1.0f);
	glm::vec3 ambientColor = lightColor * glm::vec3(0.1f);
	glm::vec3 specularColor = lightColor * glm::vec3(1.5f);
	shader.SetUniform("spotLight.ambient", ambientColor);
	shader.SetUniform("spotLight.diffuse", diffuseColor);
	shader.SetUniform("spotLight.specular", specularColor);

	shader.SetUniform("spotLight.position", Position);
	shader.SetUniform("spotLight.constant", 1.0f);
	shader.SetUniform("spotLight.linear", 0.009f);
	shader.SetUniform("spotLight.quadratic", 0.0032f);

	shader.SetUniform("spotLight.direction",Forward);
	shader.SetUniform("spotLight.cutOff", glm::cos(glm::radians(3.5f)));
	shader.SetUniform("spotLight.outerCutOff", glm::cos(glm::radians(7.0f)));

}
