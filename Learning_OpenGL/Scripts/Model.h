#pragma once

#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"
#include "Shader.h"

class Model
{
public:
	glm::mat4 TempTransformMatrix;
	Model(std::vector<Mesh> meshes);
	void Draw(Shader& shader);
private:
	std::vector<Mesh> Meshes;
};

