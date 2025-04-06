#pragma once
#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using namespace std;

class Shader
{
public :
	unsigned int ShaderProgramId;
private:
	unsigned int VertexShaderId;
	unsigned int FragmentShaderId;

public:
	Shader(string vertexPath, string fragmentPath);
	~Shader();
	void Activate();
	void SetUniform(string name, int i1);
	void SetUniform(string name, float f1);
	void SetUniform(string name, glm::mat4 matrix);
	void SetUniform(string name, glm::vec3 vector);
	void SetUniform(string name, float v1, float v2, float v3);
	void SetUniform(string name, float v1, float v2, float v3, float v4);
private:
	void Construct(const char* vertexPath,  const char* fragmentPath);
};

