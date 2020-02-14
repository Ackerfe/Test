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
		std::vector<GLuint> mTextures;
	public:

		ACube(glm::vec3 position, float sideLength, GLuint frontSprite, GLuint backSprite, GLuint leftSprite,
			GLuint rightSprite, GLuint topSprite, GLuint bottomSprite, MultiSprite* multiSprite);
		~ACube();

		glm::vec3 getPosition() { return mPosition; }
		float getCollisionRadius() { return mSideLength; }
		void renderEntity();




	};
}
