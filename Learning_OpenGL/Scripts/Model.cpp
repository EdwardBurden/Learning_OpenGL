#include "Model.h"

Model::Model(std::vector<Mesh> meshes)
{
	TempTransformMatrix = glm::mat4(1);
	Meshes = meshes;
}

void Model::Draw(Shader& shader)
{
	//model = glm::translate(model, glm::vec3(2.0f));
	//model = glm::scale(model, glm::vec3(0.01f));
	for (size_t i = 0; i < Meshes.size(); i++)
	{
		Meshes[i].BindTextures(TempTransformMatrix, shader);
		Meshes[i].Draw();
	}
}
