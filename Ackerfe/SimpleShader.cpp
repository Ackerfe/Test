#include "SimpleShader.h"


namespace Ackerfe
{
	GLuint compileLinkSimpleShaders(const std::string & vertShaderFilePath, const std::string & fragShaderFilePath)
	{
		GLuint vertShaderID = glCreateShader(GL_VERTEX_SHADER);

		if (vertShaderID == 0) 
		{
			throwConsoleError("OpenGL couldn't create the vertex shader.");
		}

		std::ifstream vertFile(vertShaderFilePath);
		
		if (!vertFile.is_open())
		{
			throwConsoleError("OpenGL couldn't open the vertex file, check the file name");
		}

		std::string fileContents = "";
		std::string tempLine = "";
		
		while (std::getline(vertFile, tempLine))
		{
			fileContents += tempLine + "\n";
		};

		vertFile.close();

		const char* contentsPtr=fileContents.c_str();

		glShaderSource(vertShaderID, 1, &contentsPtr, nullptr);
		glCompileShader(vertShaderID);

		GLint completed = 0;
		glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &completed);
		
		if (completed == GL_FALSE) 
		{
			GLint maxLength = 0;
			glGetShaderiv(vertShaderID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(vertShaderID, maxLength, &maxLength, &errorLog[0]);

			std::printf("%s \n", &errorLog[0]);

			glDeleteShader(vertShaderID);

			throwConsoleError("Failed to compile the vertex shader");
		}

		GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		if (fragShaderID == 0)
		{
			throwConsoleError("OpenGL couldn't create the fragment shader.");
		}

		std::ifstream fragFile(fragShaderFilePath);

		if (!fragFile.is_open())
		{
			throwConsoleError("OpenGL couldn't open the fragment file, check the file name");
		}

		fileContents = "";
		tempLine = "";

		while (std::getline(fragFile, tempLine))
		{
			fileContents += tempLine + "\n";
		};

		fragFile.close();

		contentsPtr = fileContents.c_str();

		glShaderSource(fragShaderID, 1, &contentsPtr, nullptr);
		glCompileShader(fragShaderID);

		completed = 0;
		glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &completed);

		if (completed == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragShaderID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(fragShaderID, maxLength, &maxLength, &errorLog[0]);

			std::printf("%s \n", &errorLog[0]);

			glDeleteShader(fragShaderID);

			throwConsoleError("Failed to compile the fragment shader");
		}

		GLuint programID = glCreateProgram();

		glAttachShader(programID, vertShaderID);
		glAttachShader(programID, fragShaderID);

		glLinkProgram(programID);

		completed = 0;
		glGetProgramiv(programID, GL_LINK_STATUS, (int *)&completed);

		if (completed == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> errorLog(maxLength);
			glGetProgramInfoLog(programID, maxLength, &maxLength, &errorLog[0]);

			std::printf("%s \n", &errorLog[0]);

			glDeleteShader(vertShaderID);
			glDeleteShader(fragShaderID);

			throwConsoleError("Failed to link the vertex shader and the fragment shader");
		}

		glDetachShader(programID, vertShaderID);
		glDetachShader(programID, fragShaderID);

		glDeleteShader(vertShaderID);
		glDeleteShader(fragShaderID);

		return programID;
	}
}