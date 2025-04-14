#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/transform2.hpp>
#include <gtc/type_ptr.hpp>


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Light/SpotLight.h"
#include "Light/DirectionalLight.h"
#include "Light/PointLight.h"
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "ModelLoader.h"
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

	//Texture container("Resources/container2.png", GL_RGBA);
	//Texture containerSpecular("Resources/container2_specular.png", GL_RGBA);
	Shader lightingShader("Resources/Lit_VertexShader.glsl", "Resources/Lit_FragmentShader.glsl"); // shader for cube lit
	Shader defualtShader("Resources/default_VertexShader.glsl", "Resources/default_FragmentShader.glsl");
	//SpotLight light(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
	//PointLight pointLight(glm::vec3(4.0f, 3.0f, 0.0f), glm::vec3(0.3f, -1.0f, -0.5)); //todo make into array
	DirectionalLight dirLioght(glm::vec3(4.0f, 3.0f, 0.0f), glm::vec3(0.3f, -1.0f, -0.5));

	// cube VAO	
	Model* mothership = ModelLoader::LoadModel("Resources/Models/backpack/backpack.obj");
	Model mymodel = *mothership;
	//Model mothership("Resources/Mothership.obj");
	glm::mat4 cubeModel = glm::mat4(1.0f);
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		camera1.Update(deltaTime);
		//light.Position = camera1.Position;
		//light.Forward = camera1.Forward;
		ProcessKeyboardInput(window);

		glClearColor(0.8f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glm::mat4 cubeModel = glm::mat4(1.0f);
		//cubeModel = glm::rotate(cubeModel, rotateSpeed * deltaTime, glm::vec3(0.4f, 0.2f, 0.8f));
		//cubeModel = glm::translate(cubeModel, glm::vec3(0.0f, 0.0f, 0.0f));
		//cubeModel = glm::scale(cubeModel, glm::vec3(0.1f, 0.1f, 0.1f));

		lightingShader.Activate();
		//Vertex
		//lightingShader.SetUniform("model", cubeModel);
		lightingShader.SetUniform("view", camera1.ViewMatrix);
		lightingShader.SetUniform("projection", camera1.ProjectionMatrix);
		//Frag
		//update lighting for all lights in scene
		//light.UpdateShader(lightingShader);
		//pointLight.UpdateShader(lightingShader);
		dirLioght.UpdateShader(lightingShader);
		lightingShader.SetUniform("pointLightsNum", 1);
		lightingShader.SetUniform("material.shininessAmount", 32.0f);
		lightingShader.SetUniform("lightColor", 1.0f, 1.0f, 1.0f);
		lightingShader.SetUniform("viewPos", camera1.Position);

		mymodel.Draw(lightingShader);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
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