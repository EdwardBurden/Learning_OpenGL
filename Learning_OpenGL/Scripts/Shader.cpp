#include "Shader.h"

Shader::Shader(string vertexPath, string fragmentPath)
{
	ShaderProgramId = glCreateProgram();
	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vertexShaderSource;
	const char* fragmentShaderSource;

	ifstream vertexFile(vertexPath);
	stringstream stringStream;
	stringStream << vertexFile.rdbuf();
	string vertexString = stringStream.str();
	vertexShaderSource = vertexString.c_str();
	vertexFile.close();

	stringStream.str("");
	ifstream fragmentFile(fragmentPath);
	stringStream << fragmentFile.rdbuf();
	string tmp = stringStream.str();
	fragmentShaderSource = tmp.c_str();
	fragmentFile.close();

	Construct(vertexShaderSource, fragmentShaderSource);
}

Shader::~Shader()
{
	glDeleteShader(VertexShaderId); // may be okay doing this in construct tbh.
	glDeleteShader(FragmentShaderId);
	glDeleteProgram(ShaderProgramId);
}

void Shader::Construct(const char* vertexShader, const char* fragmentShader)
{
	int  success;
	char infoLog[512];
	// Vertex Compile
	glShaderSource(VertexShaderId, 1, &vertexShader, NULL);
	glCompileShader(VertexShaderId);
	glGetShaderiv(VertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(VertexShaderId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//Fragment Compile
	glShaderSource(FragmentShaderId, 1, &fragmentShader, NULL);
	glCompileShader(FragmentShaderId);
	glGetShaderiv(FragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(FragmentShaderId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//Shader Compile
	glAttachShader(ShaderProgramId, VertexShaderId);
	glAttachShader(ShaderProgramId, FragmentShaderId);
	glLinkProgram(ShaderProgramId);
	glGetProgramiv(ShaderProgramId, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(ShaderProgramId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::linker::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

}

void Shader::Activate()
{
	glUseProgram(ShaderProgramId);
}

void Shader::SetUniform(string name, unsigned int ui1)
{
	int vertexColorLocation = glGetUniformLocation(ShaderProgramId, name.c_str());
	glUniform1ui(vertexColorLocation, ui1);
}

void Shader::SetUniform(string name, int i1)
{
	int vertexColorLocation = glGetUniformLocation(ShaderProgramId, name.c_str());
	glUniform1i(vertexColorLocation, i1);
}

void Shader::SetUniform(string name, float f1)
{
	int vertexColorLocation = glGetUniformLocation(ShaderProgramId, name.c_str());
	glUniform1f(vertexColorLocation, f1);

}

void Shader::SetUniform(string name, glm::mat4 matrix)
{
	int vertexColorLocation = glGetUniformLocation(ShaderProgramId, name.c_str());
	glUniformMatrix4fv(vertexColorLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetUniform(string name, glm::vec3 vector)
{
	int vertexColorLocation = glGetUniformLocation(ShaderProgramId, name.c_str());
	glUniform3f(vertexColorLocation, vector.x, vector.y, vector.z);
}

void Shader::SetUniform(string name, float v1, float v2, float v3)
{
	int vertexColorLocation = glGetUniformLocation(ShaderProgramId, name.c_str());
	glUniform3f(vertexColorLocation, v1, v2, v3);
}

void Shader::SetUniform(string name, float v1, float v2, float v3, float v4)
{
	int vertexColorLocation = glGetUniformLocation(ShaderProgramId, name.c_str());
	glUniform4f(vertexColorLocation, v1, v2, v3, v4);
}
