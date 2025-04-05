#pragma once
#include <stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Texture
{
public:
	unsigned int TextureId;
	Texture(const char* path, int level);
};

