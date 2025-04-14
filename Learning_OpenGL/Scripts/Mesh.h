#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <iostream>
#include <vector>
#include <glm.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "Shader.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int Id;
	std::string type;
	string path;  // we store the path of the texture to compare with other textures
};

class Mesh
{
public:
	glm::mat4 Tranform;
	Mesh( std::vector<Vertex> verts, std::vector<Texture> tex, std::vector<unsigned int> inds);
	void BindTextures(glm::mat4 parent, Shader& shader);
	void Draw();

private:
	const char* MaterialStructPath = "material.";
	const char* DiffusePrefix = "texture_diffuse";
	const char* SpecularPrefix = "texture_specular";

	unsigned int VAOId;
	unsigned int VBOId;
	unsigned int EBOId;

	

	std::vector<Vertex> Vertices;
	std::vector<Texture> Textures;
	std::vector<unsigned int> Indices;

	void Setup();
};

