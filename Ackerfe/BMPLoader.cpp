#include "BMPLoader.h"
#include "AckerfeErrorHandler.h"
#include <stdio.h>

namespace Ackerfe
{
	GLuint AckerfeBMPLoader(std::string BMPFilePath)
	{
		unsigned char header[54];
		unsigned int dataPos;
		unsigned int width, height;
		unsigned int imageSize;

		unsigned char* data;

		const char* filePathPtr = BMPFilePath.c_str();

		FILE* file;

		errno_t fileErr = fopen_s(&file, filePathPtr, "r");
		if (!file)
			throwError("BMP File Error", "BMP File" + BMPFilePath + " could not be opened");

		if (fread(header, 1, 54, file) != 54)
			throwError("BMP File Error", "BMP File" + BMPFilePath + " is not a bitmap file (the header is longer than 54 bytes)");

		if (header[0] != 'B' || header[1] != 'M')
			throwError("BMP File Error", "BMP File" + BMPFilePath + " is not a bitmap file (it could be formatted uncorrectly)");

		if (*(int*)&(header[0x1E]) != 0)
			throwError("BMP File Error", "BMP File" + BMPFilePath + " is not the correct type of bitmap file (not a 24bpp file)");

		if (*(int*)&(header[0x1C]) != 24)
			throwError("BMP File Error", "BMP File" + BMPFilePath + " is not the correct type of bitmap file (not a 24bpp file)");
		
		dataPos = *(int*)&(header[0x0A]);
		imageSize = *(int*)&(header[0x22]);
		width = *(int*)&(header[0x12]);
		height = *(int*)&(header[0x16]);

		if (imageSize == 0)
			imageSize = width * height * 3;

		if (dataPos == 0)
			dataPos = 54;

		data = new unsigned char[imageSize];

		fread(data, 1, imageSize, file);

		fclose(file);

		GLuint textureID;
		glGenTextures(1, &textureID);

		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

		delete[] data;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		//not sure if needed
		glGenerateMipmap(GL_TEXTURE_2D);

		return textureID;
	}
}