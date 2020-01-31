#pragma once
#include <glm-0.9.9.7/glm/glm.hpp>


namespace Ackerfe
{
	enum FrustumCullingType { RADIUS };

	class SpatialEntity
	{

	public:
		glm::vec3 getPosition() { return mPosition; }
		FrustumCullingType getCollisionType() { return mCollisionType; }
		virtual float getCollisionRadius();
		virtual void renderEntity();

	protected:
		glm::vec3 mPosition;
		FrustumCullingType mCollisionType = FrustumCullingType::RADIUS;
	};
}
