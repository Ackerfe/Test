#pragma once
#include "MultiSprite.h"
#include <glm-0.9.9.7/glm/glm.hpp>
#include <vector>
#include <math.h>
#include "ImageLoad.h"
#include "SpatialEntity.h"

namespace Ackerfe
{
	class ACube : public SpatialEntity
	{
		MultiSprite* mMultiSprite;
		float mSideLength;
		std::vector<std::string> mTextures;
	public:

		ACube(glm::vec3 position, float sideLength, std::string firstTextureFilePath, std::string secondTextureFilePath, std::string thirdTextureFilePath, 
			std::string fourthTextureFilePath, std::string fifthTextureFilePath, std::string sixthTextureFilePath, MultiSprite* multiSprite);
		~ACube();

		glm::vec3 getPosition() { return mPosition; }
		float getCollisionRadius() { return mSideLength; }
		void renderEntity();




	};
}
