#pragma once
#include <glm-0.9.9.7/glm/glm.hpp>
#include <vector>

namespace Ackerfe
{
	class ParticleEmitterCone
	{
		float mParticlesPerTimeFrame = 0.0f;
		unsigned int mParticleTime = 0;
		unsigned int mParticlesInWorld = 0;
		unsigned int mParticleLife = 0;
		glm::vec3 mPosition;
		glm::vec3 mTravelVec;
		float mEmitterSize = 0.0f;
		float mMaxDisplacement = 0.0f;
		std::vector<int> mParticleLives;
		std::vector<glm::vec3> mTravelDirs;
		std::vector<glm::vec3> mCurrentPositions;

	public:
		ParticleEmitterCone();
		~ParticleEmitterCone();

		void init(glm::vec3 position, float emitterSize, glm::vec3 travelVec, float maxDisplacement, int particlesInWorld, unsigned int particleLife);

		void loopParticles(unsigned int msDeltaTime);

		std::vector<glm::vec3> getParticlePosition();
	};
}
