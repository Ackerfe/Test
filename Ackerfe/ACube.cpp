#include "ACube.h"



namespace Ackerfe
{
	ACube::ACube(glm::vec3 position, float sideLength, std::string firstTextureFilePath, std::string secondTextureFilePath, std::string thirdTextureFilePath,
		std::string fourthTextureFilePath, std::string fifthTextureFilePath, std::string sixthTextureFilePath, MultiSprite* multiSprite)
		: mSideLength(sideLength), mMultiSprite(multiSprite)
	{
		mPosition = position;
		mTextures.push_back(firstTextureFilePath);
		mTextures.push_back(secondTextureFilePath);
		mTextures.push_back(thirdTextureFilePath);
		mTextures.push_back(fourthTextureFilePath);
		mTextures.push_back(fifthTextureFilePath);
		mTextures.push_back(sixthTextureFilePath);

	}
	ACube::~ACube()
	{
	}
	void ACube::renderEntity()
	{
		float halfSideLength = mSideLength / 2;

		//front
		mMultiSprite->addSprite(Ackerfe::loadPng(mTextures[0]), 0.0f,
			Ackerfe::Vertex(mPosition.x - halfSideLength, mPosition.y - halfSideLength, mPosition.z - halfSideLength, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x - halfSideLength, mPosition.y + halfSideLength, mPosition.z - halfSideLength, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x + halfSideLength, mPosition.y - halfSideLength, mPosition.z - halfSideLength, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x + halfSideLength, mPosition.y + halfSideLength, mPosition.z - halfSideLength, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)));
	

		//right
		mMultiSprite->addSprite(Ackerfe::loadPng(mTextures[1]), 0.0f,
			Ackerfe::Vertex(mPosition.x + halfSideLength, mPosition.y - halfSideLength, mPosition.z - halfSideLength, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x + halfSideLength, mPosition.y + halfSideLength, mPosition.z - halfSideLength, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x + halfSideLength, mPosition.y - halfSideLength, mPosition.z + halfSideLength, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x + halfSideLength, mPosition.y + halfSideLength, mPosition.z + halfSideLength, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)));

		//bottom
		mMultiSprite->addSprite(Ackerfe::loadPng(mTextures[2]), 0.0f,
			Ackerfe::Vertex(mPosition.x - halfSideLength, mPosition.y - halfSideLength, mPosition.z + halfSideLength, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x - halfSideLength, mPosition.y - halfSideLength, mPosition.z - halfSideLength, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x + halfSideLength, mPosition.y - halfSideLength, mPosition.z + halfSideLength, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x + halfSideLength, mPosition.y - halfSideLength, mPosition.z - halfSideLength, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)));

		//left
		mMultiSprite->addSprite(Ackerfe::loadPng(mTextures[3]), 0.0f,
			Ackerfe::Vertex(mPosition.x - halfSideLength, mPosition.y - halfSideLength, mPosition.z + halfSideLength, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x - halfSideLength, mPosition.y + halfSideLength, mPosition.z + halfSideLength, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x - halfSideLength, mPosition.y - halfSideLength, mPosition.z - halfSideLength, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x - halfSideLength, mPosition.y + halfSideLength, mPosition.z - halfSideLength, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)));

		//back
		mMultiSprite->addSprite(Ackerfe::loadPng(mTextures[4]), 0.0f,
			Ackerfe::Vertex(mPosition.x - halfSideLength, mPosition.y - halfSideLength, mPosition.z + halfSideLength, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x - halfSideLength, mPosition.y + halfSideLength, mPosition.z + halfSideLength, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x + halfSideLength, mPosition.y - halfSideLength, mPosition.z + halfSideLength, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x + halfSideLength, mPosition.y + halfSideLength, mPosition.z + halfSideLength, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)));

		//top
		mMultiSprite->addSprite(Ackerfe::loadPng(mTextures[5]), 0.0f,
			Ackerfe::Vertex(mPosition.x - halfSideLength, mPosition.y + halfSideLength, mPosition.z - halfSideLength, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x - halfSideLength, mPosition.y + halfSideLength, mPosition.z + halfSideLength, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x + halfSideLength, mPosition.y + halfSideLength, mPosition.z - halfSideLength, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
			Ackerfe::Vertex(mPosition.x + halfSideLength, mPosition.y + halfSideLength, mPosition.z + halfSideLength, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)));

		
	}
}