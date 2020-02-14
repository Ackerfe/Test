#pragma once
#include "MultiSprite.h"
#include <glm-0.9.9.7/glm/glm.hpp>
#include <vector>
#include <math.h>
#include "SpatialEntity.h"
#include "ACollision.h"
#include "GL/glew.h"

namespace Ackerfe
{
	class ACube : public SpatialEntity
	{
		MultiSprite* mMultiSprite;
		float mSideLength;
		std::vector<GLuint> mTextures;
		ACollAABB mBox;
	public:

		ACube(glm::vec3 position, float sideLength, GLuint firstTextureFilePath, GLuint secondTextureFilePath, GLuint thirdTextureFilePath, 
			GLuint fourthTextureFilePath, GLuint fifthTextureFilePath, GLuint sixthTextureFilePath, MultiSprite* multiSprite);
		~ACube();

		glm::vec3 getPosition() { return mPosition; }
		float getCollisionRadius() { return mSideLength; }
		void renderEntity();

		ACollAABB* getBox() { return &mBox; }




	};
}
