#include "Model.h"

Model::Model(std::vector<Mesh> meshes)
{
	Meshes = meshes;
}

void Model::Draw(Shader& shader)
{
	glm::mat4 model = glm::mat4(1);
	//model = glm::translate(model, glm::vec3(2.0f));
	//model = glm::scale(model, glm::vec3(0.01f));
	for (size_t i = 0; i < Meshes.size(); i++)
	{
		Meshes[i].BindTextures(model, shader);
		Meshes[i].Draw();
	}
}
