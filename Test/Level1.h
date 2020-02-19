#include "InputHandler.h"
#include "OSInterface.h"
#include "ImageLoad.h"
#include "SpatialSceneGraphOct.h"
#include "AAudio.h"
#include "ErrHandler.h"
#include "AMeshRenderer.h"
#include "Particles.h"
#include "Skybox.h"
#include "InitShaders.h"
#include "GUI.h"
#include "Cameras.h"

class Level1
{
	Ackerfe::GUI* mGUI;
	bool mTravel = false;

	int mScreenWidth;
	int mScreenHeight;

	Ackerfe::Camera3D mCamera;
	Ackerfe::OSInterface* mWindow;
	Ackerfe::InputHandler* mInput = nullptr;
	Ackerfe::InitShaders mShaderSet;
	FMOD::Sound* mNewSound;
	FMOD::System* mSystem;

	Ackerfe::AMeshRenderer mAsteroid1;
	Ackerfe::AMeshRenderer mAsteroid2;
	Ackerfe::AMeshRenderer mAsteroid3;

	Ackerfe::AMeshRenderer mGate;
	Ackerfe::AMeshRenderer mGateRing;

	Ackerfe::AMeshRenderer mCloud;

	Ackerfe::AMeshRenderer mGateParticles;

	Ackerfe::ParticleEmitterCone mGateParticles1;
	Ackerfe::ParticleEmitterCone mGateParticles2;

	Ackerfe::Skybox mSkybox;

	glm::mat4 mGateMatrix = glm::mat4(1.0f);
	glm::mat4 mGateRingMatrix = glm::mat4(1.0f);
	glm::mat4 mCloudMatrix = glm::mat4(1.0f);
	std::vector<glm::mat4> mAsteroidModelMatrices1;
	std::vector<glm::mat4> mAsteroidModelMatrices2;
	std::vector<glm::mat4> mAsteroidModelMatrices3;
public:
	void init(Ackerfe::Camera3D &camera, Ackerfe::InitShaders &shaderSet, int screenWidth, int screenHeight, Ackerfe::OSInterface* window, Ackerfe::GUI* gui, Ackerfe::InputHandler* input);
	void level1Loop();
	void render();
	bool setTravel();
};


