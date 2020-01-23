#pragma once
#include <GL/glew.h>
#include <string>

namespace Ackerfe
{
	GLuint loadBmp(std::string filePath);
	GLuint loadPng(std::string filePath);
}
