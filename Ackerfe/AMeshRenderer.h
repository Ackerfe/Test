#pragma once
#include <vector>
#include <glm-0.9.9.7/glm/glm.hpp>
#include <GL/glew.h>
#include "AAssImp.h"
#include "ACollision.h"
#include <assimp/mesh.h>

namespace Ackerfe
{
	struct AMesh
	{
		std::vector<unsigned short> indices;
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals;

		ACollAABB mBox;
		GLuint textureID;
	};

	class AMeshRenderer
	{
	public:
		AMeshRenderer();
		~AMeshRenderer();

		void init();
		void addMesh(char* filePath, GLuint texture);
		void prepareMesh();
		void renderMesh();
		AMesh *getMesh() { return &mMeshes[0]; }

		glm::vec3 getBoundingSpherePos(AMesh &mesh);
		float getBoundingSphereRadius(AMesh &mesh, glm::vec3 &avgPos);

	private:
		GLuint mVao = 0;
		GLuint mVbo = 0;
		GLuint mVertexBuffer = 0;
		GLuint mUvBuffer = 0;
		GLuint mNormalBuffer = 0;
		GLuint mIndexBuffer = 0;
		std::vector<AMesh> mMeshes;
	};


}

