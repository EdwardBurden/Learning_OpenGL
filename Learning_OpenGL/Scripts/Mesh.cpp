#include "Mesh.h"


Mesh::Mesh(std::vector<Vertex> verts, std::vector<Texture> tex, std::vector<unsigned int> inds)
{
	//Tranform = transform;//
	//glm::mat4 model
	//Tranform = glm::scale(Tranform, glm::vec3(0.2f));

	Vertices = verts;
	Textures = tex;
	Indices = inds;
	Setup();
}

void Mesh::BindTextures(glm::mat4 parent, Shader& shader)
{
	glm::mat4 model = glm::mat4(1);
	model *= parent;
	model *= Tranform;

	shader.SetUniform("model", model);
	if (Textures.empty())
		return;
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for (unsigned int i = 0; i < Textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		string number;
		string name = Textures[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);
		string  matTexture = (MaterialStructPath + name + number).c_str();
		shader.SetUniform(matTexture, i);
		glBindTexture(GL_TEXTURE_2D, Textures[i].Id);
	}
	glActiveTexture(GL_TEXTURE0);
}

void Mesh::Draw()
{
	// draw mesh
	glBindVertexArray(VAOId);
	glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


void Mesh::Setup()
{
	glGenBuffers(1, &VBOId);
	glGenBuffers(1, &EBOId);
	glGenVertexArrays(1, &VAOId);

	glBindVertexArray(VAOId);
	glBindBuffer(GL_ARRAY_BUFFER, VBOId);
	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertices), &Vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), &Indices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	
	glBindVertexArray(0);
}