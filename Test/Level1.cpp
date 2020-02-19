#include "Level1.h"
#include <glm-0.9.9.7/glm/glm.hpp>
#include <random>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm-0.9.9.7/glm/gtc/quaternion.hpp>
#include <glm-0.9.9.7/glm/gtx/quaternion.hpp>
#include <glm-0.9.9.7/glm/gtx/euler_angles.hpp>
#include <glm-0.9.9.7/glm/gtc/type_ptr.hpp>

void Level1::init(Ackerfe::Camera3D &camera, Ackerfe::InitShaders &shaderSet, int screenWidth, int screenHeight, Ackerfe::OSInterface * window, Ackerfe::GUI * gui, Ackerfe::InputHandler* input)
{
		mScreenWidth = screenWidth;
		mScreenHeight = screenHeight;
		mShaderSet = shaderSet;
		mCamera = camera;
		mWindow = window;
		mGUI = gui;
		mInput = input;

		for (float k = -10.0f; k < 200.0f; k += 5.0f)
		{
			std::random_device rd; 
			std::mt19937 eng(rd()); 
			std::uniform_real_distribution<> distr(-5.0f, 5.0f);
			glm::mat4 tempMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(k, k, k));
			tempMatrix *= glm::eulerAngleXYZ((float)(distr(eng)), (float)(-distr(eng)), k);
			tempMatrix *= glm::translate(glm::mat4(1.0f), glm::vec3((float)distr(eng), (float)(-distr(eng)), k));
			mAsteroidModelMatrices1.push_back(tempMatrix);
		}
		for (float k = -10.0f; k < 200.0f; k += 5.0f)
		{
			std::random_device rd;
			std::mt19937 eng(rd());
			std::uniform_real_distribution<> distr(-5.0f, 5.0f);
			glm::mat4 tempMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(k, k, k));
			tempMatrix *= glm::eulerAngleXYZ((float)(distr(eng)), (float)(-distr(eng)), k);
			tempMatrix *= glm::translate(glm::mat4(1.0f), glm::vec3((float)distr(eng), (float)(-distr(eng)), k));
			mAsteroidModelMatrices2.push_back(tempMatrix);
		}
		for (float k = -10.0f; k < 200.0f; k += 5.0f)
		{
			std::random_device rd;
			std::mt19937 eng(rd());
			std::uniform_real_distribution<> distr(-5.0f, 5.0f);
			glm::mat4 tempMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(k, k, k));
			tempMatrix *= glm::eulerAngleXYZ((float)(distr(eng)), (float)(-distr(eng)), k);
			tempMatrix *= glm::translate(glm::mat4(1.0f), glm::vec3((float)distr(eng), (float)(-distr(eng)), k));
			mAsteroidModelMatrices3.push_back(tempMatrix);
		}

		mGateParticles1.init(glm::vec3(900.0f, 0.0f, 900.0f), 0.1f, glm::vec3(0.0f, 0.0f, 0.01f), 0.005f,
			10000, 5000);
		mGateParticles2.init(glm::vec3(900.0f, 0.0f, 900.0f), 0.1f, glm::vec3(0.0f, 0.0f, -0.01f), 0.005f,
			10000, 5000);

		mAsteroid1.init();
		mAsteroid2.init();
		mAsteroid3.init();
		mGate.init();
		mGateRing.init();
		mCloud.init();
		mGateParticles.init();

		std::string temp = "Meshes/skybox.obj";
		char* test = &temp[0];
		mSkybox.init(test,
			"Texture/Skyboxes/Skybox3/right.png", "Texture/Skyboxes/Skybox3/left.png",
			"Texture/Skyboxes/Skybox3/top.png", "Texture/Skyboxes/Skybox3/bottom.png",
			"Texture/Skyboxes/Skybox3/front.png", "Texture/Skyboxes/Skybox3/back.png");
		mSkybox.prepare();

		temp = "Meshes/SmallParticle.obj";
		test = &temp[0];
		mGateParticles.addMesh(test, Ackerfe::loadPng("Texture/GateInside.png"));
		mGateParticles.prepareMesh();

		temp = "Meshes/CloudGroup.obj";
		test = &temp[0];
		mCloud.addMesh(test, Ackerfe::loadPng("Texture/Dust.png"));
		mCloud.prepareMesh();

		temp = "Meshes/JumpDisk.obj";
		test = &temp[0];
		mGateRing.addMesh(test, Ackerfe::loadPng("Texture/GateInside.png"));
		mGateRing.prepareMesh();

		temp = "Meshes/JumpGate.obj";
		test = &temp[0];
		mGate.addMesh(test, Ackerfe::loadPng("Texture/gateTexture.png"));
		mGate.prepareMesh();

		temp = "Meshes/A2.obj";
		test = &temp[0];
		mAsteroid3.addMesh(test, Ackerfe::loadPng("Texture/asteroidTexture.png"));
		mAsteroid3.prepareMesh();

		temp = "Meshes/Asteroid_2_LOW_MODEL_.obj";
		test = &temp[0];
		mAsteroid2.addMesh(test, Ackerfe::loadPng("Texture/asteroidTexture.png"));
		mAsteroid2.prepareMesh();

		temp = "Meshes/Asteroid_1_LOW_MODEL_.obj";
		test = &temp[0];
		mAsteroid1.addMesh(test, Ackerfe::loadPng("Texture/asteroidTexture.png"));
		mAsteroid1.prepareMesh();


		
		mGateRingMatrix *= glm::scale(glm::mat4(1.0f), glm::vec3(5.2f));
		mGateRingMatrix *= glm::translate(glm::mat4(1.0f), glm::vec3(173.0769f, 0.0f, 173.0769f));

		mGateMatrix *= glm::scale(glm::mat4(1.0f), glm::vec3(3.0f, 3.0f, 5.0f));
		mGateMatrix *= glm::translate(glm::mat4(1.0f), glm::vec3(300.0f, 0.0f, 188.0f));

		mCloudMatrix *= glm::scale(glm::mat4(1.0f), glm::vec3(3000.0f, 3000.0f, 3000.0f));
		mCloudMatrix *= glm::translate(glm::mat4(1.0f), glm::vec3(-4.0f, 0.0f, 3.25f));
	
}

void Level1::level1Loop()
{
	unsigned int lastTime = SDL_GetTicks();

	while (mTravel == false)
	{
		unsigned int deltaTime = SDL_GetTicks() - lastTime;
		lastTime = SDL_GetTicks();

		mCamera.update();

		glUseProgram(mShaderSet.getMMeshProgramID());
		glUniformMatrix4fv(mShaderSet.getMMeshPerspectiveID(), 1, GL_FALSE, &mCamera.getPerspectiveMatrix()[0][0]);
		glUniformMatrix4fv(mShaderSet.getMMeshCameraMatrixID(), 1, GL_FALSE, &mCamera.getCameraMatrix()[0][0]);
		glUniformMatrix4fv(mShaderSet.getMMeshModelCameraMatrixID(), 1, GL_FALSE, &mCamera.getModelCameraMatrix()[0][0]);
		glUniform3f(mShaderSet.getMMeshLightPositionID(), -10000.0f, 0.05f, -1.5f);
		glUniform3f(mShaderSet.getMMeshLightColourID(), 1.0f, 1.0f, 1.0f);
		glUniform1f(mShaderSet.getMMeshLightIntensityID(), 9000000.0f);
		glUniform3f(mShaderSet.getMMeshEyePositionID(), mCamera.getPosition().x, mCamera.getPosition().y, mCamera.getPosition().z);
		glUniformMatrix4fv(mShaderSet.getMMeshModelMatrixID(), 1, GL_FALSE, &mGateMatrix[0][0]);
		mGate.renderMesh();

		for (unsigned int i = 0; i < mAsteroidModelMatrices1.size(); i++)
		{
			float beta = 45.0f / 500000.0f;

			mAsteroidModelMatrices1[i] *= glm::mat4(
				cos(beta), 0.0f, sin(beta), 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				-sin(beta), 0.0f, cos(beta), 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f);

			mAsteroidModelMatrices1[i] *= glm::mat4(1.0f);

			glUniformMatrix4fv(mShaderSet.getMMeshModelMatrixID(), 1, GL_FALSE, &mAsteroidModelMatrices1[i][0][0]);
			mAsteroid1.renderMesh();
		}

		for (unsigned int i = 0; i < mAsteroidModelMatrices2.size(); i++)
		{
			float alpha = 30.0f / 200000.0f;

			mAsteroidModelMatrices2[i] *= glm::mat4(
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, cos(alpha), -sin(alpha), 0.0f,
				0.0f, sin(alpha), cos(alpha), 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f);

			mAsteroidModelMatrices2[i] *= glm::mat4(1.0f);

			glUniformMatrix4fv(mShaderSet.getMMeshModelMatrixID(), 1, GL_FALSE, &mAsteroidModelMatrices2[i][0][0]);

			mAsteroid2.renderMesh();
		}

		for (unsigned int i = 0; i < mAsteroidModelMatrices3.size(); i++)
		{

			float gamma = 90.0f / 500000.0f;

			mAsteroidModelMatrices3[i] *= glm::mat4(
				cos(gamma), -sin(gamma), 0.0f, 0.0f,
				sin(gamma), cos(gamma), 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f);

			mAsteroidModelMatrices3[i] *= glm::mat4(1.0f);

			

			glUniformMatrix4fv(mShaderSet.getMMeshModelMatrixID(), 1, GL_FALSE, &mAsteroidModelMatrices3[i][0][0]);
			mAsteroid3.renderMesh();

		}

		glUseProgram(mShaderSet.getMSkyboxProgramID());
		glUniformMatrix4fv(mShaderSet.getMSkyboxPerspectiveID(), 1, GL_FALSE, &mCamera.getProjectionMatrix()[0][0]);

		glm::mat4 modifiedCameraMatrix = mCamera.getCameraMatrix();
		modifiedCameraMatrix[3][0] = 0.0f;
		modifiedCameraMatrix[3][1] = 0.0f;
		modifiedCameraMatrix[3][2] = 0.0f;

		glUniformMatrix4fv(mShaderSet.getMSkyboxCameraMatrixID(), 1, GL_FALSE, &modifiedCameraMatrix[0][0]);
		glUniformMatrix4fv(mShaderSet.getMSkyboxModelMatrixID(), 1, GL_FALSE, &glm::mat4(1.0f)[0][0]);
		glUniform3f(mShaderSet.getMSkyboxLightPositionID(), 0, 0, 0);

		mSkybox.render();

		glUseProgram(mShaderSet.getMCloudProgramID());
		glUniformMatrix4fv(mShaderSet.getMCloudPerspectiveID(), 1, GL_FALSE, &mCamera.getPerspectiveMatrix()[0][0]);
		glUniformMatrix4fv(mShaderSet.getMCloudCameraMatrixID(), 1, GL_FALSE, &modifiedCameraMatrix[0][0]);
		glUniformMatrix4fv(mShaderSet.getMCloudModelCameraMatrixID(), 1, GL_FALSE, &mCamera.getModelCameraMatrix()[0][0]);


		for (unsigned int i = 0; i < 5; i++)
		{
			float alpha = 45.0f / 200000.0f;

			mGateRingMatrix *= glm::rotate(glm::mat4(1.0f), alpha, glm::vec3(0.0f, 0.0f, 173.0769f));
			mGateRingMatrix *= glm::mat4(1.0f);


			
			glUniformMatrix4fv(mShaderSet.getMCloudModelMatrixID(), 1, GL_FALSE, &mGateRingMatrix[0][0]);
			glUniform1f(mShaderSet.getMCloudTransparencyID(), 0.15f);
			mGateRing.renderMesh();
		}

		for (unsigned int i = 0; i < 5; i++)
		{
			
			float beta = 45.0f / 400000.0f;

			mCloudMatrix *= glm::translate(glm::mat4(1.0f), glm::vec3(4.0f, 0.0f, -3.25f));
			mCloudMatrix *= glm::mat4(
				cos(beta), 0.0f, sin(beta), 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				-sin(beta), 0.0f, cos(beta), 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f);

			mCloudMatrix *= glm::mat4(1.0f);
			mCloudMatrix *= glm::translate(glm::mat4(1.0f), glm::vec3(-4.0f, 0.0f, 3.25f));

			
			glUniform1f(mShaderSet.getMCloudTransparencyID(), 0.08f);
			glUniformMatrix4fv(mShaderSet.getMCloudModelMatrixID(), 1, GL_FALSE, &mCloudMatrix[0][0]);
			mCloud.renderMesh();
		}

		glUseProgram(mShaderSet.getMBillboardProgramID());
		glUniformMatrix4fv(mShaderSet.getMBillboardPerspectiveID(), 1, GL_FALSE, &mCamera.getProjectionMatrix()[0][0]);
		glUniformMatrix4fv(mShaderSet.getMBillboardCameraMatrixID(), 1, GL_FALSE, &mCamera.getCameraMatrix()[0][0]);
		glUniform1f(mShaderSet.getMBillboardScaleID(), 0.1f);

		mGateParticles1.loopParticles(deltaTime);
		std::vector<glm::vec3> vector = mGateParticles1.getParticlePosition();
		std::vector<glm::mat4> particleMatrices;

		for (unsigned int i = 0; i < vector.size(); i++)
		{
			particleMatrices.push_back(glm::translate(glm::mat4(1.0f), vector[i]));
		}
		mGateParticles2.loopParticles(deltaTime);
		std::vector<glm::vec3> vector2 = mGateParticles2.getParticlePosition();
		std::vector<glm::mat4> particleMatrices2;

		for (unsigned int i = 0; i < vector2.size(); i++)
		{
			particleMatrices2.push_back(glm::translate(glm::mat4(1.0f), vector2[i]));
		}
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		for (unsigned int i = 0; i < particleMatrices.size(); i++)
		{
			glUniformMatrix4fv(mShaderSet.getMBillboardModelMatrixID(), 1, GL_FALSE, &particleMatrices[i][0][0]);
			mGateParticles.renderMesh();
		}
		for (unsigned int i = 0; i < particleMatrices2.size(); i++)
		{
			glUniformMatrix4fv(mShaderSet.getMBillboardModelMatrixID(), 1, GL_FALSE, &particleMatrices2[i][0][0]);
			mGateParticles.renderMesh();
		}
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUseProgram(0);
		mInput->inputQueue();
		mWindow->swapBuffer();
	}
}

void Level1::render()
{
}

bool Level1::setTravel()
{
	return false;
}
