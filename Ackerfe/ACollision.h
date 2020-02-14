#pragma once
#include "glm-0.9.9.7/glm/glm.hpp"
#include <vector>


namespace Ackerfe
{
	struct ACollSphr
	{
		glm::vec3* pos;
		float radius;
	};

	struct ACollAABB
	{
		glm::vec3 *pos;
		glm::vec3 maxOffset;
		glm::vec3 minOffset;
	};

	struct ACollPlane
	{
		ACollPlane(glm::vec3 newNormal, float newOffset)
		{
			normal = newNormal; offset = newOffset;
		}
		glm::vec3 normal;
		float offset;
	};

	struct ACollCnvx
	{
		glm::vec3 *pos;
		std::vector<ACollPlane> planes;
	};

	bool sphrSphrColl(ACollSphr *first, ACollSphr *second);
	bool aabbAABBColl(ACollAABB *first, ACollAABB *second);

	bool sphrPlaneSide(ACollSphr *sphere, ACollPlane *plane);
	bool sphrCnvxColl(ACollSphr *spher, ACollCnvx *cnvxShape);

	bool aabbPlaneSide(ACollAABB *box, ACollPlane *plane);
	bool aabbCnvx(ACollAABB *box, ACollCnvx *cnvxShape);
}
