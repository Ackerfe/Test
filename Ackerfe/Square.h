#pragma once
#include <GL/glew.h>
#include <string>
namespace Ackerfe
{
	class Square
	{
		GLuint mUVBuffer = 0;
		GLuint mTexture = 0;
		GLuint mVboID = 0;
		
	public:
		Square(std::string textureFilePath);
		~Square();
		void draw();
		void textureDraw();
	};
}
