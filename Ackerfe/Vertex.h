#pragma once
#include <GL/glew.h>
	class Vertex
	{
	public:
		Vertex() {}
		Vertex(float x, float y, float u, float v)
			:mX(x), mY(y), mU(u), mV(v) {}

		GLfloat mX = 0.0f;
		GLfloat mY = 0.0f;
		GLfloat mU = 0.0f;
		GLfloat mV = 0.0f;

	};

