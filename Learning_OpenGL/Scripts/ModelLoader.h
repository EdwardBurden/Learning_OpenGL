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
			aiProcess_Triangulate | aiProcess_FlipUVs); //FlipUvs needs looking at


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
		vector<Texture> textures_loaded;
		string directory = path.substr(0, path.find_last_of('/'));
		std::vector<Mesh> meshes;
		ProcessNode(textures_loaded, scene->mRootNode, scene, meshes, directory);
		Model* model = new Model(meshes);
		return model;
	};

private:

	static void ProcessNode(vector<Texture> &textures_loaded, aiNode* node, const aiScene* scene, std::vector<Mesh>& meshes, string& directory) {

		if (node == nullptr)
			return;		
		
		
		
		for (size_t i = 0; i < node->mNumMeshes; i++)
		{
			unsigned int meshIndex = node->mMeshes[i];
			aiMesh* mesh = scene->mMeshes[meshIndex];
			Mesh meshMade = ProcessMesh(textures_loaded, mesh, scene, directory);
			meshMade.Tranform = ConvertMatrixToGLMFormat(node->mTransformation);
			meshes.push_back(meshMade);
		}

		for (size_t i = 0; i < node->mNumChildren; i++)
		{

			ProcessNode(textures_loaded, node->mChildren[i], scene, meshes, directory);
		}
	}

	static inline glm::mat4 ConvertMatrixToGLMFormat(const aiMatrix4x4& from)
	{
		glm::mat4 to;
		//the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
		to[0][0] = from.a1; to[1][0] = from.a2; to[2][0] = from.a3; to[3][0] = from.a4;
		to[0][1] = from.b1; to[1][1] = from.b2; to[2][1] = from.b3; to[3][1] = from.b4;
		to[0][2] = from.c1; to[1][2] = from.c2; to[2][2] = from.c3; to[3][2] = from.c4;
		to[0][3] = from.d1; to[1][3] = from.d2; to[2][3] = from.d3; to[3][3] = from.d4;
		return to;
	}


	static Mesh ProcessMesh(vector<Texture>& textures_loaded, aiMesh* mesh, const aiScene* scene, string directory) {
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
		if (matIndex > 0) { // dont care for mat 0
			aiMaterial* mat = scene->mMaterials[matIndex];
			aiString name;
			mat->Get(AI_MATKEY_NAME, name);
			std::vector<Texture> diffuseMaps = Loadtextures(textures_loaded,mat, aiTextureType_DIFFUSE, "texture_diffuse", directory);
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			std::vector<Texture> specularMaps = Loadtextures(textures_loaded, mat, aiTextureType_SPECULAR, "texture_specular", directory);
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}
		Mesh meshmade( vertices, textures, indices);
		return meshmade;
	}

	static std::vector<Texture> Loadtextures(vector<Texture>& textures_loaded, aiMaterial* mat, aiTextureType type, string typeName, string& directory) {
		std::vector<Texture> textures;
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString path;
			mat->GetTexture(type, i, &path);
			bool skip = false;
			for (unsigned int j = 0; j < textures_loaded.size(); j++)
			{
				if (std::strcmp(textures_loaded[j].path.data(), path.C_Str()) == 0) {
					textures.push_back(textures_loaded[j]);
					skip = true;
					break;
				}

			}
			if (skip)
				continue;
			Texture texture;
			texture.Id = LoadTextureFromFile(path, directory);
			texture.type = typeName;
			texture.path = path.C_Str();
			textures.push_back(texture);
			textures_loaded.push_back(texture);
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
		case 3:
			format = GL_RGB;
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