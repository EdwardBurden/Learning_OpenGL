#pragma once

#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Model.h"
#include "Shader.h"


class ModelLoader {
public:
	static Model* LoadModel(string path) {
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path,
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType);


		if (nullptr == scene) {
			const char* errorString = importer.GetErrorString();
			std::cout << errorString << std::endl;
			return nullptr;
		}

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
			return nullptr;
		}

		string directory = path.substr(0, path.find_last_of('/'));
		std::vector<Mesh> meshes;

		ProcessNode(scene->mRootNode, scene, meshes, directory);
		Model* model = new Model(meshes);
		return model;
	};

private:

	static void ProcessNode(aiNode* node, const aiScene* scene, std::vector<Mesh>& meshes, string& directory) {

		if (node == nullptr)
			return;

		for (size_t i = 0; i < node->mNumMeshes; i++)
		{
			unsigned int meshIndex = node->mMeshes[i];
			aiMesh* mesh = scene->mMeshes[meshIndex];
			Mesh meshMade = ProcessMesh(mesh, scene, directory);
			meshes.push_back(meshMade);
		}

		for (size_t i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene, meshes , directory);
		}
	}


	static Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene, string directory) {
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<Texture> textures;

		for (size_t i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			glm::vec3 position, normal;
			position.x = mesh->mVertices[i].x;
			position.y = mesh->mVertices[i].y;
			position.z = mesh->mVertices[i].z;
			vertex.Position = position;
			normal.x = mesh->mNormals[i].x;
			normal.y = mesh->mNormals[i].y;
			normal.z = mesh->mNormals[i].z;
			vertex.Normal = normal;

			if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
			{
				glm::vec2 vec;
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = vec;
			}
			else
				vertex.TexCoords = glm::vec2(0.0f, 0.0f);

			vertices.push_back(vertex);
		}

		//indices
		for (size_t i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (size_t j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		unsigned int matIndex = mesh->mMaterialIndex;
		if (matIndex >= 0) {
			aiMaterial* mat = scene->mMaterials[matIndex];
			std::vector<Texture> diffuseMaps = Loadtextures(mat, aiTextureType_DIFFUSE, "texture_diffuse", directory);
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			std::vector<Texture> specularMaps = Loadtextures(mat, aiTextureType_SPECULAR, "texture_specular", directory);
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}

		Mesh meshmade(vertices, textures, indices);
		return meshmade;
	}

	static std::vector<Texture> Loadtextures(aiMaterial* mat, aiTextureType type, string typeName, string& directory) {
		std::vector<Texture> textures;

		for (size_t i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString path;
			mat->GetTexture(type, i, &path);
			Texture texture;
			texture.Id = LoadTextureFromFile(path, directory);
			texture.type = typeName;
			textures.push_back(texture);
		}

		return textures;
	}


	static unsigned int LoadTextureFromFile(aiString path, string& directory)
	{
		unsigned int textureId;
		stbi_set_flip_vertically_on_load(true);
		int width, height, nrChannels;

		string fullPath = directory + '/' + path.C_Str();
		unsigned char* data = stbi_load(fullPath.c_str(), &width, &height, &nrChannels, 0);

		GLenum format;
		switch (nrChannels)
		{
			case 1:	format = GL_RED;
				break;
			case 3:	format = GL_RGB;
				break;
			case 4:	format = GL_RGBA;
				break;
			default:
				break;
		}

		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
		return textureId;
	}

};