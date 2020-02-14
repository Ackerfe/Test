#pragma once
#include <vector>
#include <glm-0.9.9.7/glm/glm.hpp>
namespace Ackerfe
{
	void loadAssImp(char *filePath, std::vector<unsigned short> &indices,
		std::vector<glm::vec3> &vertices, std::vector<glm::vec2> &uvs,
		std::vector<glm::vec3> &normals);

	
}

