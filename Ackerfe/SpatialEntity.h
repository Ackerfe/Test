#pragma once
#include <glm-0.9.9.7/glm/glm.hpp>
#include "ACollision.h"


namespace Ackerfe
{
	enum FrustumCullingType { RADIUS };

	class SpatialEntity
	{

	public:

		SpatialEntity();
		~SpatialEntity();

		glm::vec3 getPosition() { return mPosition; }
		FrustumCullingType getCollisionType() { return mCollisionType; }
		virtual float getCollisionRadius();
		virtual void renderEntity();
		virtual ACollAABB* getBox() { return nullptr; }

	protected:
		glm::vec3 mPosition;
		FrustumCullingType mCollisionType = FrustumCullingType::RADIUS;
	};
}
