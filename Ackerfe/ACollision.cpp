#include "ACollision.h"
#include <iostream>
namespace Ackerfe
{
	bool sphrSphrColl(ACollSphr *first, ACollSphr *second)
	{
	
		if (((first->pos->x - second->pos->x) * (first->pos->x - second->pos->x) +
			(first->pos->y - second->pos->y) * (first->pos->y - second->pos->y) +
			(first->pos->z - second->pos->z) * (first->pos->z - second->pos->z) < (first->radius + second->radius) * (first->radius + second->radius)))
		{
			//std::cout <<"DISTANCE: "<<std::endl<<glm::length(*first->pos - *second->pos) << std::endl << std::endl << std::endl << std::endl;
			return true;
		}
		
		return false;
	}

	bool aabbAABBColl(ACollAABB *first, ACollAABB *second)
	{
		if (first->pos->x + first->maxOffset.x <=
			second->pos->x + second->minOffset.x)
		{
			return false;
		}
		if (first->pos->y + first->maxOffset.y <=
			second->pos->y + second->minOffset.y)
		{
			return false;
		}
		if (first->pos->z + first->maxOffset.z <=
			second->pos->z + second->minOffset.z)
		{
			return false;
		}
		if (second->pos->x + second->maxOffset.x <=
			first->pos->x + first->minOffset.x)
		{
			return false;
		}
		if (second->pos->y + second->maxOffset.y <=
			first->pos->y + first->minOffset.y)
		{
			return false;
		}
		if (second->pos->z + second->maxOffset.z <=
			first->pos->z + first->minOffset.z)
		{
			return false;
		}
		return true;
	}

	bool sphrPlaneSide(ACollSphr *sphere, ACollPlane *plane)
	{
		if (glm::dot(plane->normal, *sphere->pos) + plane->offset < -sphere->radius)
			return false;
		
		return true;
	}

	bool sphrCnvxColl(ACollSphr *sphere, ACollCnvx *cnvxShape)
	{
		for (unsigned int i = 0; i < cnvxShape->planes.size(); i++)
		{
			if (!sphrPlaneSide(sphere, &cnvxShape->planes[i]))
				return false;
			
		}
		return true;
	}

	bool aabbPlaneSide(ACollAABB *box, ACollPlane *plane)
	{
		glm::vec3 minRelToPlane;
		glm::vec3 maxRelToPlane;
		if (plane->normal.x >= 0.0f)
		{
			minRelToPlane.x = box->pos->x + box->minOffset.x;
			maxRelToPlane.x = box->pos->x + box->maxOffset.x;
		}
		else
		{
			minRelToPlane.x = box->pos->x + box->maxOffset.x;
			maxRelToPlane.x = box->pos->x + box->minOffset.x;
		}
		if (plane->normal.y >= 0.0f)
		{
			minRelToPlane.y = box->pos->y + box->minOffset.y;
			maxRelToPlane.y = box->pos->y + box->maxOffset.y;
		}
		else
		{
			minRelToPlane.y = box->pos->y + box->maxOffset.y;
			maxRelToPlane.y = box->pos->y + box->minOffset.y;
		}
		if (plane->normal.z >= 0.0f)
		{
			minRelToPlane.z = box->pos->z + box->minOffset.z;
			maxRelToPlane.z = box->pos->z + box->maxOffset.z;
		}
		else
		{
			minRelToPlane.z = box->pos->z + box->maxOffset.z;
			maxRelToPlane.z = box->pos->z + box->minOffset.z;
		}

		if (glm::dot(plane->normal, minRelToPlane) + plane->offset > 0)
		{
			return true;
		}
		if (glm::dot(plane->normal, maxRelToPlane) + plane->offset > 0)
		{
			return true;
		}
		return false;
	
	}

	bool aabbCnvx(ACollAABB *box, ACollCnvx *cnvxShape)
	{
		for (unsigned int i = 0; i < cnvxShape->planes.size(); i++)
		{
			if (!aabbPlaneSide(box, &cnvxShape->planes[i]))
			{
				return false;
			}
		}
		return true;
	
	}
}
