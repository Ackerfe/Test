#pragma once
#include <GL/glew.h>

namespace Ackerfe {
	class Triangle
	{
		GLuint mVboID=0;
	
	public:
		Triangle();
		~Triangle();
		void draw();
	};
}
