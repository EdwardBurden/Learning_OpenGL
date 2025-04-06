#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "DirectionalLight.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
using namespace std;

static void ProcessKeyboardInput(GLFWwindow* window);
static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
static void MouseInputCallback(GLFWwindow* window, double xpos, double ypos);

Camera camera1;
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
float rotateSpeed = 1.0f;
float lastX = 400, lastY = 300;
bool firstMouse = true;

// ------------------------------------------------------------------
float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
glm::vec3(0.0f,  -1.0f,  0.0f),
glm::vec3(2.0f,  5.0f, -15.0f),
glm::vec3(-1.5f, -2.2f, -2.5f),
glm::vec3(-3.8f, -2.0f, -12.3f),
glm::vec3(2.4f, -0.4f, -3.5f),
glm::vec3(-1.7f,  3.0f, -7.5f),
glm::vec3(1.3f, -2.0f, -2.5f),
glm::vec3(1.5f,  2.0f, -2.5f),
glm::vec3(1.5f,  0.2f, -1.5f),
glm::vec3(-1.3f,  1.0f, -1.5f)
};


unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};


int main()
{
	// window setup
	glfwInit();
	GLFWmonitor* primary = glfwGetPrimaryMonitor();
	const char* name = glfwGetMonitorName(primary);

	int count;
	GLFWmonitor** monitors = glfwGetMonitors(&count);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 600, name, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, MouseInputCallback);
	glEnable(GL_DEPTH_TEST);

	Texture container("Resources/container2.png", GL_RGBA);
	Texture containerSpecular("Resources/container2_specular.png", GL_RGBA);
	Shader lightingShader("Resources/Lit_VertexShader.glsl", "Resources/Lit_FragmentShader.glsl"); // shader for cube lit
	Shader defualtShader("Resources/default_VertexShader.glsl", "Resources/default_FragmentShader.glsl");
	DirectionalLight dirLight(glm::vec3(0.0f, 3.0f, 0.0f), glm::vec3(0.3f, -1.0f, -0.5));



	// cube VAO	
	unsigned int VBO, VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	int stride = (3 * sizeof(float) * 2) + (2 * sizeof(float));
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float) * 2));
	glEnableVertexAttribArray(2);

	// light VAO
	unsigned int L_VBO;
	glGenVertexArrays(1, &L_VBO);
	glBindVertexArray(L_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
	glEnableVertexAttribArray(0);

	//glm::mat4 cubeModel = glm::mat4(1.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		camera1.Update(deltaTime);
		ProcessKeyboardInput(window);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//cubeModel = glm::rotate(cubeModel, rotateSpeed * deltaTime, glm::vec3(0.4f, 0.2f, 0.8f));

		lightingShader.Activate();
		//Vertex
		//lightingShader.SetUniform("model", cubeModel);
		lightingShader.SetUniform("view", camera1.ViewMatrix);
		lightingShader.SetUniform("projection", camera1.ProjectionMatrix);
		//Frag
		//update lighting for all lights in scene
		dirLight.UpdateShader(lightingShader);
		lightingShader.SetUniform("material.diffuseMap", 0); // 0 = sampler 0
		lightingShader.SetUniform("material.specularMap", 1);
		lightingShader.SetUniform("material.shininessAmount", 32.0f);
		lightingShader.SetUniform("lightColor", 1.0f, 1.0f, 1.0f);
		lightingShader.SetUniform("viewPos", camera1.Position);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, container.TextureId);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, containerSpecular.TextureId);
		glBindVertexArray(VAO);
		for (unsigned int i = 0; i <10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			lightingShader.SetUniform("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//glDrawArrays(GL_TRIANGLES, 0, 36);

		lightModel = glm::mat4(1.0f);
		//lightModel = glm::translate(lightModel, dirLight.Position);
		//lightModel = glm::scale(lightModel, glm::vec3(0.2f));;

		//dirLight.Forward.x = glm::sin(currentFrame/5)*5;
		//dirLight.Forward.y = glm::cos(currentFrame) * 2;
		//dirLight.Forward.z = glm::cos(currentFrame/5)*5;

	//	dirLight.Position = -dirLight.Forward;
		glm::mat4 rotate = glm::lookAt(dirLight.Position, dirLight.Position + dirLight.Forward, glm::vec3(0.0f, 1.0f, 0.0f));
		lightModel = glm::inverse(rotate);


		defualtShader.Activate();
		dirLight.UpdateShader(defualtShader);
		defualtShader.SetUniform("model", lightModel);
		defualtShader.SetUniform("view", camera1.ViewMatrix);
		defualtShader.SetUniform("projection", camera1.ProjectionMatrix);
		glBindVertexArray(L_VBO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}

static void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

static void MouseInputCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse) // initially set to true
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
	lastX = xpos;
	lastY = ypos;

	const float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	camera1.UpdateCameraLook(xoffset, yoffset);
}

static void ProcessKeyboardInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		if (rotateSpeed == 1.0f)
			rotateSpeed = 0.0f;
		else
			rotateSpeed = 1.0f;
	}
	glm::vec2 directionInput = glm::vec2(0, 0);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		directionInput.y += 1;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		directionInput.y -= 1;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		directionInput.x += 1;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		directionInput.x -= 1;
	}

	if (directionInput.x != 0 || directionInput.y != 0)
	{
		directionInput = glm::normalize(directionInput);
		camera1.UpdateCameraPosition(directionInput);
	}
}