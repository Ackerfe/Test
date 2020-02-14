#include "ACube.h"



namespace Ackerfe
{
	ACube::ACube(glm::vec3 position, float sideLength, GLuint frontSprite, GLuint backSprite, GLuint leftSprite,
		GLuint rightSprite, GLuint topSprite, GLuint bottomSprite, MultiSprite* multiSprite)
		: mSideLength(sideLength), mMultiSprite(multiSprite)
	{
		mPosition = position;
		mTextures.push_back(frontSprite);
		mTextures.push_back(backSprite);
		mTextures.push_back(leftSprite);
		mTextures.push_back(rightSprite);
		mTextures.push_back(topSprite);
		mTextures.push_back(bottomSprite);

	}
	ACube::~ACube()
	{
	}
	void ACube::renderEntity()
	{
		float halfSideLength = mSideLength / 2;

		//front
		mMultiSprite->addSprite(mTextures[0], 0.0f,
			Ackerfe::Vertex(mPosition.x - halfSideLength, mPosition.y - halfSideLength, mPosition.z - halfSideLength, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x - halfSideLength, mPosition.y + halfSideLength, mPosition.z - halfSideLength, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x + halfSideLength, mPosition.y - halfSideLength, mPosition.z - halfSideLength, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x + halfSideLength, mPosition.y + halfSideLength, mPosition.z - halfSideLength, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)));


		//right
		mMultiSprite->addSprite(mTextures[1], 0.0f,
			Ackerfe::Vertex(mPosition.x + halfSideLength, mPosition.y - halfSideLength, mPosition.z - halfSideLength, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x + halfSideLength, mPosition.y + halfSideLength, mPosition.z - halfSideLength, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x + halfSideLength, mPosition.y - halfSideLength, mPosition.z + halfSideLength, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x + halfSideLength, mPosition.y + halfSideLength, mPosition.z + halfSideLength, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)));

		//bottom
		mMultiSprite->addSprite(mTextures[2], 0.0f,
			Ackerfe::Vertex(mPosition.x - halfSideLength, mPosition.y - halfSideLength, mPosition.z + halfSideLength, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x - halfSideLength, mPosition.y - halfSideLength, mPosition.z - halfSideLength, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x + halfSideLength, mPosition.y - halfSideLength, mPosition.z + halfSideLength, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x + halfSideLength, mPosition.y - halfSideLength, mPosition.z - halfSideLength, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)));

		//left
		mMultiSprite->addSprite(mTextures[3], 0.0f,
			Ackerfe::Vertex(mPosition.x - halfSideLength, mPosition.y - halfSideLength, mPosition.z + halfSideLength, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x - halfSideLength, mPosition.y + halfSideLength, mPosition.z + halfSideLength, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x - halfSideLength, mPosition.y - halfSideLength, mPosition.z - halfSideLength, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x - halfSideLength, mPosition.y + halfSideLength, mPosition.z - halfSideLength, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)));

		//back
		mMultiSprite->addSprite(mTextures[4], 0.0f,
			Ackerfe::Vertex(mPosition.x - halfSideLength, mPosition.y - halfSideLength, mPosition.z + halfSideLength, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x - halfSideLength, mPosition.y + halfSideLength, mPosition.z + halfSideLength, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x + halfSideLength, mPosition.y - halfSideLength, mPosition.z + halfSideLength, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x + halfSideLength, mPosition.y + halfSideLength, mPosition.z + halfSideLength, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)));

		//top
		mMultiSprite->addSprite(mTextures[5], 0.0f,
			Ackerfe::Vertex(mPosition.x - halfSideLength, mPosition.y + halfSideLength, mPosition.z - halfSideLength, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x - halfSideLength, mPosition.y + halfSideLength, mPosition.z + halfSideLength, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x + halfSideLength, mPosition.y + halfSideLength, mPosition.z - halfSideLength, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x + halfSideLength, mPosition.y + halfSideLength, mPosition.z + halfSideLength, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)));


	}
}