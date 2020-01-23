#include "Square.h"
#include "ImageLoad.h"
namespace Ackerfe
{


	Square::Square(std::string textureFilePath)
	{
		

		glGenBuffers(1, &mVboID);
		static const GLfloat vboData[] =
		{
			-1.0f, -1.0f,
			-1.0f, 0.0f,
			0.0f, -1.0f,
			-1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, -1.0f
		};
		glBindBuffer(GL_ARRAY_BUFFER, mVboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vboData), vboData, GL_STATIC_DRAW);

		mTexture = Ackerfe::loadPNG(textureFilePath);
		glGenBuffers(1, &mUVBuffer);

		glBindBuffer(GL_ARRAY_BUFFER, mUVBuffer);
		static const GLfloat uvData[] =
		{
			0.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 1.0f,		/*PNG uv Coordinates*/
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f

			/*
			0.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 0.0f,		Bitmap uv coordinates
			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f */
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(uvData), uvData, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	Square::~Square()
	{
	}

	void Square::draw()
	{
		glBindBuffer(GL_ARRAY_BUFFER, mVboID);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Square::textureDraw()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mTexture);
		glUniform1i(mTexture, 0);

		glBindBuffer(GL_ARRAY_BUFFER, mVboID);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, mUVBuffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}