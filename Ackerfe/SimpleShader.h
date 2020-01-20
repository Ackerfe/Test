#pragma once
#include <string>
#include <GL/glew.h>
#include <fstream>
#include <vector>
#include "AckerfeErrorHandler.h"

namespace Ackerfe 
{
	GLuint compileLinkSimpleShaders(const std::string &vertShaderFilePath, const std::string &fragShaderFilePath);

}
