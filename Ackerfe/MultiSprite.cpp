#include "MultiSprite.h"


namespace Ackerfe {
	
	MultiSprite::MultiSprite() : mVbo(0), mVao(0)
	{
	}

	MultiSprite::~MultiSprite()
	{
	}

	void MultiSprite::init()
	{
		if (mVao != 0)
		{	
			throwError("error", "You tried to call init on for a sprite batch twice");
			return;
		}

		glGenVertexArrays(1, &mVao);
		glBindVertexArray(mVao);
		glGenBuffers(1, &mVbo);
		glBindBuffer(GL_ARRAY_BUFFER, mVbo);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,mX));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,mU));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, mColour));

		glBindVertexArray(0);
	}

	void MultiSprite::clearCache()
	{
		mSprites.clear();
		mSpriteBatches.clear();
	}

	void MultiSprite::prepareBatches()
	{
		if (mSprites.empty())
		{
			throwError("error", "You tried to prepare sprite batches without any sprites");
			return;
		}

		mSortingSprites.resize(mSprites.size());
		for (size_t i = 0;i < mSprites.size();i++)
		{
			mSortingSprites[i] = &mSprites[i];
			
		}
		std::sort(mSortingSprites.begin(), mSortingSprites.end(), compareTexture);

		std::vector<Vertex> vertices;
		vertices.resize(mSortingSprites.size() * 6);

		GLuint currentOffset = 0;
		GLuint currentVertex = 0;
		
		mSpriteBatches.emplace_back(mSortingSprites[0]->mTextureID, 6, currentOffset);
		vertices[currentVertex++] = mSortingSprites[0]->mTopLeft;
		vertices[currentVertex++] = mSortingSprites[0]->mBottomLeft;
		vertices[currentVertex++] = mSortingSprites[0]->mBottomRight;
		vertices[currentVertex++] = mSortingSprites[0]->mBottomRight;
		vertices[currentVertex++] = mSortingSprites[0]->mTopRight;
		vertices[currentVertex++] = mSortingSprites[0]->mTopLeft;
		std::cout << mSortingSprites[0]->mBottomLeft.mV;

		currentOffset += 6;

		for (size_t currentSprite = 1; currentSprite < mSortingSprites.size(); currentSprite++)
		{
			if (mSortingSprites[currentSprite]->mTextureID != mSortingSprites[currentSprite - 1]->mTextureID) {
				mSpriteBatches.emplace_back(mSortingSprites[currentSprite]->mTextureID, 6, currentOffset);
			}

			else {
				mSpriteBatches.back().mNumVertices += 6;
			}

			vertices[currentVertex++] = mSortingSprites[currentSprite]->mTopLeft;
			std::cout << currentSprite;
			std::cout << mSortingSprites[currentSprite]->mTopLeft.mY;
			vertices[currentVertex++] = mSortingSprites[currentSprite]->mBottomLeft;
			vertices[currentVertex++] = mSortingSprites[currentSprite]->mBottomRight;
			vertices[currentVertex++] = mSortingSprites[currentSprite]->mBottomRight;
			vertices[currentVertex++] = mSortingSprites[currentSprite]->mTopRight;
			vertices[currentVertex++] = mSortingSprites[currentSprite]->mTopLeft;

			currentOffset += 6;

		}

		glBindBuffer(GL_ARRAY_BUFFER, mVbo);

		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
		
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		

	}

	void MultiSprite::renderBatches()
	{
		
		glBindVertexArray(mVao);
		
		for (unsigned int i = 0; i < mSpriteBatches.size(); i++)
		{
			
			glBindTexture(GL_TEXTURE_2D, mSpriteBatches[i].mTextureID);
			glDrawArrays(GL_TRIANGLES, mSpriteBatches[i].mOffset, mSpriteBatches[i].mNumVertices);
		}
		
		glBindVertexArray(0);
	}

	void MultiSprite::addSprite(glm::vec4 destRect, glm::vec4 uvRect, unsigned int textureID, float depth, ColourRGBA8 colour)
	{
		Vertex bottomLeft(destRect.x, destRect.y, depth, uvRect.x, uvRect.y, colour);
		Vertex bottomRight(destRect.x + destRect.z, destRect.y, depth, uvRect.x + uvRect.z, uvRect.y, colour);
		Vertex topLeft(destRect.x, destRect.y + destRect.w, depth, uvRect.x, uvRect.y + uvRect.w, colour);
		Vertex topRight(destRect.x + destRect.z, destRect.y + destRect.w, depth, uvRect.x + uvRect.z, uvRect.y + uvRect.w, colour);

		mSprites.emplace_back(textureID, depth, bottomLeft, topLeft, bottomRight, topRight);
	}

}