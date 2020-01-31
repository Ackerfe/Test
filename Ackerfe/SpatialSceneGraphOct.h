#pragma once
#include <glm-0.9.9.7/glm/glm.hpp>
#include <vector>
#include <cmath>
#include "SpatialEntity.h"
namespace Ackerfe
{
	class SpatialSceneGraphOct
	{
		float mMinX, mMaxX;
		float mMinY, mMaxY;
		float mMinZ, mMaxZ;

		std::vector<SpatialEntity*> mEntitiesWithin;
		std::vector<SpatialSceneGraphOct*> mOctsWithin;

	public:
		SpatialSceneGraphOct();
		SpatialSceneGraphOct(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
		~SpatialSceneGraphOct();

		void addToStack(std::vector<SpatialEntity*>* entityStack, std::vector<SpatialSceneGraphOct*>* graphStack);
		bool doesEntityBelongHere(SpatialEntity* entity);

		void addEntityToGraph(SpatialEntity* entity);

		glm::vec3 getCenter();
		float getXSideLength() { return std::abs(mMaxX - mMinX); }

		void createChildren();

		std::vector<glm::vec3> getPoints();

	};
}
