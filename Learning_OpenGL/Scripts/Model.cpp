#include "Model.h"

Model::Model(std::vector<Mesh> meshes)
{
	Meshes = meshes;
}

void Model::Draw(Shader& shader)
{
	for (size_t i = 0; i < Meshes.size(); i++)
	{
		Meshes[i].BindTextures(shader);
		Meshes[i].Draw();
	}
}
