#pragma once
#include <GL/glew.h>
#include <vector>
#include <algorithm>
#include "ErrHandler.h"
#include "Vertex.h"
namespace Ackerfe
{
	

	struct Sprite
	{
		Sprite(GLuint textureID,float depth, Vertex &bottomLeft,  Vertex &topLeft,  Vertex &bottomRight, Vertex &topRight)
			: mTextureID(textureID), mDepth(depth), mBottomLeft(bottomLeft), mBottomRight(bottomRight), mTopLeft(topLeft), mTopRight(topRight) {}


		GLuint mTextureID = 0;
		float mDepth = 0.0f;

		Vertex mBottomLeft;
		Vertex mBottomRight;
		Vertex mTopLeft;
		Vertex mTopRight;
	};

	struct SpriteBatch
	{
		SpriteBatch(GLuint textureID, GLuint numVertices, GLuint offset)
			: mTextureID(textureID), mNumVertices(numVertices), mOffset(offset) {}

		GLuint mTextureID = 0;
		GLuint mNumVertices = 0;
		GLuint mOffset = 0;
	};
	class MultiSprite
	{
		static bool compareTexture(Sprite* a, Sprite* b)
		{
			return (a->mTextureID < b->mTextureID);
		}

		std::vector<Sprite*> mSortingSprites;
		std::vector<Sprite> mSprites;
		std::vector<SpriteBatch> mSpriteBatches;

		GLuint mVbo = 0;
		GLuint mVao = 0;

	public:
		MultiSprite();
		~MultiSprite();

		void init();
		void clearCache();
		void addSprite(GLuint textureID, float depth,  Vertex &bottomLeft, Vertex &topLeft, Vertex &bottomRight, Vertex &topRight)
		{
			mSprites.emplace_back(textureID, depth, bottomLeft, topLeft, bottomRight, topRight);
		}
		void prepareBatches();
		void renderBatches();
	};
}
