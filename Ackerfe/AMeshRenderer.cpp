#include "AMeshRenderer.h"
#include <iostream>
#include <math.h>

namespace Ackerfe
{

	AMeshRenderer::AMeshRenderer()
	{
	}

	AMeshRenderer::~AMeshRenderer()
	{
	}

	void AMeshRenderer::init()
	{
		glGenVertexArrays(1, &mVao);
		glBindVertexArray(mVao);

		glGenBuffers(1, &mVertexBuffer);
		glGenBuffers(1, &mUvBuffer);
		glGenBuffers(1, &mNormalBuffer);
		glGenBuffers(1, &mIndexBuffer);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, mUvBuffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, mNormalBuffer);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void AMeshRenderer::addMesh(char * filePath, GLuint texture)
	{
		AMesh tempMesh;
		tempMesh.textureID = texture;
		loadAssImp(filePath, tempMesh.indices, tempMesh.vertices, tempMesh.uvs,
			tempMesh.normals);
		mMeshes.push_back(tempMesh);
	}

	void AMeshRenderer::prepareMesh()
	{
		glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, mMeshes[0].vertices.size() * sizeof(glm::vec3),
			&mMeshes[0].vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, mUvBuffer);
		glBufferData(GL_ARRAY_BUFFER, mMeshes[0].uvs.size() * sizeof(glm::vec2),
			&mMeshes[0].uvs[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, mNormalBuffer);
		glBufferData(GL_ARRAY_BUFFER, mMeshes[0].normals.size() * sizeof(glm::vec3),
			&mMeshes[0].normals[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			mMeshes[0].indices.size() * sizeof(unsigned short), &mMeshes[0].indices[0],
			GL_STATIC_DRAW);

		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void AMeshRenderer::renderMesh()
	{
		glBindVertexArray(mVao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);

		glBindTexture(GL_TEXTURE_2D, mMeshes[0].textureID);

		glDrawElements(GL_TRIANGLES, mMeshes[0].indices.size(), GL_UNSIGNED_SHORT,
			(void *)0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	glm::vec3 AMeshRenderer::getBoundingSpherePos(AMesh &mesh)
	{
		
		glm::vec3 avgPos(0.0f);
		int numVerts = mesh.vertices.size();
		const float rcpNum = 1.0f / (float)numVerts;
		int count = 0;
		while (count < numVerts)
		{
			avgPos.x += mesh.vertices[count].x * rcpNum;
			avgPos.y += mesh.vertices[count].y * rcpNum;
			avgPos.z += mesh.vertices[count].z * rcpNum;
			count++;
		}

		return avgPos;
	}

	float AMeshRenderer::getBoundingSphereRadius(AMesh &mesh, glm::vec3 &avgPos) 
	{
		float maxSqDist = 0.0f;
		int numVerts = mesh.vertices.size();
		int count = 0;
		while (count < numVerts)
		{
			glm::vec3 diff = avgPos - mesh.vertices[count];

			// Note we may as well use the square length as the sqrt is very expensive and the 
			// maximum square length will ALSO be the maximum length and yet we only need to
			// do one sqrt this way :)
			const float sqDist = glm::length(diff);
			if (sqDist > maxSqDist)
			{
				maxSqDist = sqDist;
			}
			count++;
		}

		const float radius = sqrtf(maxSqDist);
		return radius;
	}
}