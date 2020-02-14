#pragma once
#include <string>
#include <GL/glew.h>
#include "AMeshRenderer.h"

namespace Ackerfe
{
	class Skybox
	{
		GLuint mTextureObject = 0;

		AMesh mMesh;

		GLuint mVao = 0;
		GLuint mVbo = 0;

		GLuint mVertexBuffer = 0;
		GLuint mUvBuffer = 0;
		GLuint mNormalBuffer = 0;
		GLuint mIndexBuffer = 0;

	public:
		Skybox();
		~Skybox();

		void init(char *filePath,
			const std::string &posXFilename, const std::string &negXFilename,
			const std::string &posYFilename, const std::string &negYFilename,
			const std::string &posZFilename, const std::string &negZFilename);

		void prepare();
		void render();
	};
}
