#include "InputHandler.h"
#include "InitFileReadWrite.h"
#include "OSInterface.h"
#include "Triangle.h"
#include "SimpleShader.h"
#include "Square.h"
#include "MultiSprite.h"
#include "imageLoad.h"
#include "Cameras.h"
#include "SpriteFont.h"
#include "ACube.h"
#include "SpatialSceneGraphOct.h"
#include "GameLogo.h"
#include "GraphicsResourceManager.h"
#include "GUI.h"
#include "MainMenu.h"
#include "AAudio.h"
#include "MessagingSystem.h"
#include "ACollision.h"
#include "ErrHandler.h"
#include "AMeshRenderer.h"
#include "Particles.h"
#include "Skybox.h"
#include <random>


/*temporarily include iostream*/
#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm-0.9.9.7/glm/gtc/quaternion.hpp>
#include <glm-0.9.9.7/glm/gtx/quaternion.hpp>
#include <glm-0.9.9.7/glm/gtx/euler_angles.hpp>
#include <glm-0.9.9.7/glm/gtc/type_ptr.hpp>

int main(int argc, char** argv)
{
	Ackerfe::OSInterface osInterface;
	osInterface.init();
	osInterface.createWindow("Window", 512, 512, 0);

	Ackerfe::GraphicsResourceManager graphics;

	Ackerfe::CorrespondentManager manager;
	manager.init();

	Ackerfe::Correspondent quitCorrespondent;
	std::string corrString = "QuitGame";
	quitCorrespondent.init(&manager, corrString);

	GameLogo gameLogo;
	gameLogo.init("Logo.vert", "Logo.frag", 512, 512, glm::vec2(0.0f, 0.0f), 1.0f, &osInterface, &graphics);
	gameLogo.logoUpdateRenderLoop();

	Ackerfe::GUI gui;
	gui.init("GUI", &manager, &osInterface);

	Ackerfe::InputHandler newInput;
	newInput.init(&manager, &osInterface);

	MainMenu mainMenu;
	mainMenu.init(&graphics, "Logo.vert", "Logo.frag", 512, 512, glm::vec2(0.0f, 0.0f), 1.0f, &osInterface, &gui, &newInput);
	mainMenu.mainMenuLoop();

	Ackerfe::relativeMouseMotionToggle();

	Ackerfe::AAudio audio;
	std::string tempString = "SoundMap1.txt";
	audio.init(tempString, &manager);

	bool doQuit = false;


	GLuint programID = Ackerfe::compileLinkSimpleShaders("TextureVert.vert", "TextureFrag.frag");
	GLuint secondProgramID = Ackerfe::compileLinkSimpleShaders("SimpleVert.vert", "SimpleFrag.frag");

	GLint shaderPerspectiveID = glGetUniformLocation(programID, "Perspective");
	GLint shaderCameraMatrixID = glGetUniformLocation(programID, "CameraMatrix");
	GLint shaderModelMatrixID = glGetUniformLocation(programID, "ModelMatrix");
	GLint shaderLightPositionID = glGetUniformLocation(programID, "LightPosition");
	GLint shaderModelCameraMatrixID = glGetUniformLocation(programID, "ModelCameraMatrix");
	GLint shaderLightColourID = glGetUniformLocation(programID, "LightColour");
	GLint shaderLightIntensityID = glGetUniformLocation(programID, "LightIntensity");

	GLuint meshProgramID = Ackerfe::compileLinkSimpleShaders("Mesh.vert", "Mesh.frag");
	GLint shaderPerspectiveIDm = glGetUniformLocation(meshProgramID, "Perspective");
	GLint shaderCameraMatrixIDm = glGetUniformLocation(meshProgramID, "CameraMatrix");
	GLint shaderModelMatrixIDm = glGetUniformLocation(meshProgramID, "ModelMatrix");
	GLint shaderLightPositionIDm = glGetUniformLocation(meshProgramID, "LightPosition");
	GLint shaderModelCameraMatrixIDm = glGetUniformLocation(meshProgramID, "ModelCameraMatrix");
	GLint shaderLightColourIDm = glGetUniformLocation(meshProgramID, "LightColour");
	GLint shaderLightIntensityIDm = glGetUniformLocation(meshProgramID, "LightIntensity");
	

	GLuint billboardProgramID = Ackerfe::compileLinkSimpleShaders("Billboard.vert", "Billboard.frag");
	GLint shaderPerspectiveIDma = glGetUniformLocation(billboardProgramID, "Perspective");
	GLint shaderCameraMatrixIDma = glGetUniformLocation(billboardProgramID, "CameraMatrix");
	GLint shaderModelMatrixIDma = glGetUniformLocation(billboardProgramID, "ModelMatrix");
	GLint shaderScaleID = glGetUniformLocation(billboardProgramID, "Scale");

	GLuint skyboxProgramID = Ackerfe::compileLinkSimpleShaders("Skybox.vert", "Skybox.frag");
	GLint skyboxPerspectiveIDma = glGetUniformLocation(skyboxProgramID, "Perspective");
	GLint skyboxCameraMatrixIDma = glGetUniformLocation(skyboxProgramID, "CameraMatrix");
	GLint skyboxModelMatrixIDma = glGetUniformLocation(skyboxProgramID, "ModelMatrix");
	GLint shaderLightColourIDma = glGetUniformLocation(skyboxProgramID, "LightPosition");


	Ackerfe::Camera2D camera2D(512, 512, glm::vec2(0.0f, 0.0f), 1.0f);
	glm::mat4 ortho = camera2D.getMatrix();

	Ackerfe::Camera3D camera3D(512, 512, glm::vec3(0.0f, 0.0f, 5.0f),
		45.0f, 1.0f, 10000.0f, glm::vec3(0.0f, 1.0f, 0.0f), &manager, 1.57f, 0.0f);

	Ackerfe::Camera3D cameraCheck(512, 512, glm::vec3(0.0f, 0.0f, 0.0f),
		45.0f, 1.0f, 20000.0f, glm::vec3(0.0f, 1.0f, 0.0f), &manager, -1.57f, 0.0f);

	Ackerfe::MultiSprite multiSprite2;
	multiSprite2.init();

	std::vector<Ackerfe::SpatialSceneGraphOct*> sceneGraphOctStack;
	std::vector<Ackerfe::SpatialEntity*> spatialEntityStack;
	float minSpace = -1000.0f;
	float maxSpace = 1000.0f;
	Ackerfe::SpatialSceneGraphOct spatialGraph(minSpace, maxSpace, minSpace, maxSpace, minSpace, maxSpace);
	spatialGraph.createChildren();
	sceneGraphOctStack.push_back(&spatialGraph);

	std::vector<Ackerfe::ACube> cubes;

	GLuint frontSprite = Ackerfe::loadPng("Texture/cyan.png");
	GLuint backSprite = Ackerfe::loadPng("Texture/green.png");
	GLuint leftSprite = Ackerfe::loadPng("Texture/blue.png");
	GLuint rightSprite = Ackerfe::loadPng("Texture/purple.png");
	GLuint topSprite = Ackerfe::loadPng("Texture/orange.png");
	GLuint bottomSprite = Ackerfe::loadPng("Texture/yellow.png");

	for (float i = -1; i <= 1; i += 1)
	{
		for (float j = -1; j < 1; j += 1)
		{
			for (float k = -1; k < 1; k += 1)
			{
				spatialGraph.addEntityToGraph(new Ackerfe::ACube(glm::vec3(i, j, k),
					0.3f, frontSprite, backSprite, leftSprite, rightSprite, topSprite,
					bottomSprite, &multiSprite2));
			}
		}
	}

	for (unsigned int i = 0; i < sceneGraphOctStack.size(); i++)
	{
		if (Ackerfe::aabbCnvx(sceneGraphOctStack[i]->getBox(), cameraCheck.getFrustum()))
		{
			sceneGraphOctStack[i]->addToStack(&spatialEntityStack, &sceneGraphOctStack);
		}
	}

	for (unsigned int i = 0; i < spatialEntityStack.size(); i++)
	{
		if (1/*Ackerfe::aABBCnvx(spatialEntityStack[i]->getBox(), cameraCheck.getFrustum())*/)
		{
			
			spatialEntityStack[i]->renderEntity();
			std::cout << "Box at " << spatialEntityStack[i]->getPosition().x << ", " << spatialEntityStack[i]->getPosition().y << ", " << spatialEntityStack[i]->getPosition().z << std::endl;
		}

	}

	multiSprite2.prepareBatches();


	

	Ackerfe::AMeshRenderer meshRenderer;
	meshRenderer.init();
	std::string temp = "Meshes/A2.obj";
	char *test = &temp[0];
	GLuint textID = Ackerfe::loadPng("Texture/asteroidTexture.png");
	meshRenderer.addMesh(test, textID);
	meshRenderer.prepareMesh();


	Ackerfe::AMeshRenderer meshRenderer2;
	meshRenderer2.init();
	temp = "Meshes/Asteroid_1_LOW_MODEL_.obj";
	test = &temp[0];
	meshRenderer2.addMesh(test, textID);
	meshRenderer2.prepareMesh();

	Ackerfe::AMeshRenderer meshRenderer3;
	meshRenderer3.init();
	temp = "Meshes/Asteroid_2_LOW_MODEL_.obj";
	test = &temp[0];
	meshRenderer3.addMesh(test, textID);
	meshRenderer3.prepareMesh();

	std::vector<glm::mat4> meshModelMatrices;

	/*for (float i = -10.0f; i < 10.0f; i += 5.0f)
	{
		for (float j = -10.0f; j < 10.0f; j += 5.0f)
		{
			for (float k = -10.0f; k < 10.0f; k += 5.0f)
			{
				glm::mat4 tempMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(k, k, k));
				tempMatrix *= glm::eulerAngleXYZ(i, j, k);
				tempMatrix *= glm::translate(glm::mat4(1.0f), glm::vec3(i, j, k));
				meshModelMatrices.push_back(tempMatrix);
			}
		}
	}*/

	int i;
	int j;
	
	std::vector<glm::mat4> meshModelMatrices2;
	std::vector<const float*> vec;
	for (float k = -10.0f; k < 200.0f; k += 5.0f)
	{
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 eng(rd()); // seed the generator
		std::uniform_real_distribution<> distr(-5.0f, 5.0f); // define the range
		glm::mat4 tempMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(k, k, k));
		tempMatrix *= glm::eulerAngleXYZ((float)(distr(eng)), (float)(-distr(eng)), k);
		tempMatrix *= glm::translate(glm::mat4(1.0f), glm::vec3((float)distr(eng), (float)(-distr(eng)), k));
		meshModelMatrices2.push_back(tempMatrix);
	}

	std::vector<glm::mat4> meshModelMatrices3;
	for (float k = -10.0f; k < 200.0f; k += 5.0f)
	{
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 eng(rd()); // seed the generator
		std::uniform_real_distribution<> distr(-2.0f, 2.0f); // define the range
		glm::mat4 tempMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(k, k, k));
		tempMatrix *= glm::eulerAngleXYZ((float)(distr(eng)), (float)(distr(eng)), k);
		tempMatrix *= glm::translate(glm::mat4(1.0f), glm::vec3((float)distr(eng), (float)(-distr(eng)), k));
		meshModelMatrices3.push_back(tempMatrix);
	}

	std::vector<glm::mat4> meshModelMatrices4;
	for (float k = -10.0f; k < 200.0f; k += 5.0f)
	{
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 eng(rd()); // seed the generator
		std::uniform_real_distribution<> distr(-3.0f, 3.0f); // define the range
		glm::mat4 tempMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(k, k, k));
		tempMatrix *= glm::eulerAngleXYZ((float)(distr(eng)), (float)(distr(eng)), k);
		tempMatrix *= glm::translate(glm::mat4(1.0f), glm::vec3((float)distr(eng), (float)(-distr(eng)), k));
		meshModelMatrices4.push_back(tempMatrix);
	}



	Ackerfe::ParticleEmitterCone pEmit;
	pEmit.init(glm::vec3(1.0f), 0.001f, glm::vec3(0.0f, 0.0f, 0.001f), 0.0005f,
		1000, 100000);

	Ackerfe::Skybox skybox;
	temp = "Meshes/skybox.obj";
	test = &temp[0];
	skybox.init(test,
		"Texture/Skyboxes/Skybox2/right.png", "Texture/Skyboxes/Skybox2/left.png",
		"Texture/Skyboxes/Skybox2/top.png", "Texture/Skyboxes/Skybox2/bottom.png",
		"Texture/Skyboxes/Skybox2/front.png", "Texture/Skyboxes/Skybox2/back.png");
	skybox.prepare();

	unsigned int lastTime = SDL_GetTicks();

	float alpha = 0.0f;
	float beta = 0.0f;
	srand(time(NULL));
	std::vector<Ackerfe::ACollSphr> meshSphr;
	bool hit = false;
	float radius;
	bool createSphr = true;
	bool printPos = true;
	
	Ackerfe::ACollSphr cameraSphr;
	Ackerfe::ACollSphr testingSphr;
	testingSphr.pos = new glm::vec3(0.0f,0.0f,0.0f);
	testingSphr.radius = 10.0f;
	while (!quitCorrespondent.getMessage())
	{
		unsigned int deltaTime = SDL_GetTicks() - lastTime;
		lastTime = SDL_GetTicks();

		
		gui.update();
		audio.update();
		camera3D.update();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);
		//triangle.textureDraw();
		glUniformMatrix4fv(shaderPerspectiveID, 1, GL_FALSE, &ortho[0][0]);
		//multiSprite3.renderBatches();
		//multiSprite.renderBatches();
		glUniformMatrix4fv(shaderPerspectiveID, 1, GL_FALSE, &camera3D.getPerspectiveMatrix()[0][0]);
		glUniformMatrix4fv(shaderModelMatrixID, 1, GL_FALSE, &camera3D.getModelMatrix()[0][0]);
		glUniformMatrix4fv(shaderCameraMatrixID, 1, GL_FALSE, &camera3D.getCameraMatrix()[0][0]);
		glUniformMatrix4fv(shaderModelCameraMatrixID, 1, GL_FALSE, &camera3D.getModelCameraMatrix()[0][0]);
		glUniform3f(shaderLightPositionID, -2000.0f, 0.5f, -1.5f);
		glUniform3f(shaderLightColourID, 1.0f, 1.0f, 1.0f);
		glUniform1f(shaderLightIntensityID, 9000000.0f);
		//multiSprite3.renderBatches();
		multiSprite2.renderBatches();

		glUseProgram(meshProgramID);

		glUniformMatrix4fv(shaderPerspectiveIDm, 1, GL_FALSE, &camera3D.getPerspectiveMatrix()[0][0]);

		glUniformMatrix4fv(shaderCameraMatrixIDm, 1, GL_FALSE, &camera3D.getCameraMatrix()[0][0]);
		glUniformMatrix4fv(shaderModelCameraMatrixIDm, 1, GL_FALSE, &camera3D.getModelCameraMatrix()[0][0]);
		glUniform3f(shaderLightPositionIDm, -10000.0f, 0.05f, -1.5f);
		glUniform3f(shaderLightColourIDm, 1.0f, 1.0f, 1.0f);
		glUniform1f(shaderLightIntensityIDm, 9000000.0f);


		//glUseProgram(billboardProgramID);
		//glUniformMatrix4fv(shaderPerspectiveIDma, 1, GL_FALSE, &camera3D.getProjectionMatrix()[0][0]);
		//glUniformMatrix4fv(shaderCameraMatrixIDma, 1, GL_FALSE, &camera3D.getCameraMatrix()[0][0]);
		//glUniform1f(shaderScaleID, 0.07f);

		//pEmit.loopParticles(deltaTime);
		//std::vector<glm::vec3> vector = pEmit.getParticlePosition();
		//std::vector<glm::mat4> particleMatrices;

		//for (unsigned int i = 0; i < vector.size(); i++)
		//{
		//	particleMatrices.push_back(glm::translate(glm::mat4(1.0f), vector[i]));
		//}


		
		for (unsigned int i = 0; i < meshModelMatrices3.size(); i++)
		{
			/*if (beta < 360.0f && beta >= 0.0f) {

				int randNum = (rand() % 3) + 1;
				beta = 45.0f/50000.0f;

				meshModelMatrices3[i] *= glm::mat4(
					cos(beta), 0.0f, sin(beta), 0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					-sin(beta), 0.0f, cos(beta), 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);

				meshModelMatrices3[i] *= glm::mat4(1.0f);

			}*/
			//else beta = 0.0f;
			glUniformMatrix4fv(shaderModelMatrixIDm, 1, GL_FALSE, &meshModelMatrices3[i][0][0]);
			meshRenderer.renderMesh();
		}

		for (unsigned int i = 0; i < meshModelMatrices2.size(); i++)
		{
			/*if (alpha < 360.0f && alpha >= 0.0f) {

			
				alpha = 30.0f/100000.0f;

				meshModelMatrices2[i] *= glm::mat4(
					1.0f, 0.0f, 0.0f, 0.0f,
					0.0f, cos(alpha), -sin(alpha), 0.0f,
					0.0f, sin(alpha), cos(alpha), 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);

				meshModelMatrices2[i] *= glm::mat4(1.0f);
				
			}*/
			

			glUniformMatrix4fv(shaderModelMatrixIDm, 1, GL_FALSE, &meshModelMatrices2[i][0][0]);

			vec.push_back((const float*)glm::value_ptr(meshModelMatrices2[i]));

			meshRenderer2.renderMesh();
		}


		for (unsigned int i = 0; i < meshModelMatrices4.size(); i++)
		{
			
			glUniformMatrix4fv(shaderModelMatrixIDm, 1, GL_FALSE, &meshModelMatrices4[i][0][0]);
			meshRenderer3.renderMesh();
		}
		


		if (createSphr)
		{
			for (unsigned int i = 0; i < meshModelMatrices2.size(); i++)
			{
				Ackerfe::ACollSphr tempSphr;
				glm::vec3 *temporary = new glm::vec3(meshRenderer2.getBoundingSpherePos(*meshRenderer2.getMesh()) * glm::vec3(vec[i][12], vec[i][13], vec[i][14]));
				tempSphr.pos = temporary;
				radius = meshRenderer2.getBoundingSphereRadius(*meshRenderer2.getMesh(), *tempSphr.pos);

				tempSphr.radius = radius;

				meshSphr.push_back(tempSphr);
				
				
				

				//std::cout << pos.x << "    " << pos.y << "    " << pos.z << std::endl;
				//std::cout << vec[i][12] << "    " << vec[i][13] << "    " << vec[i][14] << std::endl;
			}

		}

		if (printPos)
		{
			for (unsigned int i = 0; i < meshSphr.size(); i++)
			{
				std::cout << meshSphr[i].pos->x << "     " << meshSphr[i].pos->y << "     " << meshSphr[i].pos->z << std::endl << "RADIUS: " <<meshSphr[i].radius<<std::endl;
			}
			printPos = false;
		}

		for (unsigned int i = 0; i < meshSphr.size(); i++)
		{
			
			if (Ackerfe::sphrSphrColl(camera3D.getSphr(), &meshSphr[i]))
			{
				camera3D.changePosition(camera3D.getPosition()+glm::vec3(-5.0f));
			}
			
		}
	
		meshSphr.clear();

		glUseProgram(skyboxProgramID);
		glUniformMatrix4fv(skyboxPerspectiveIDma, 1, GL_FALSE, &camera3D.getProjectionMatrix()[0][0]);

		glm::mat4 modifiedCameraMatrix = camera3D.getCameraMatrix();
		modifiedCameraMatrix[3][0] = 0.0f;
		modifiedCameraMatrix[3][1] = 0.0f;
		modifiedCameraMatrix[3][2] = 0.0f;

		glUniformMatrix4fv(skyboxCameraMatrixIDma, 1, GL_FALSE, &modifiedCameraMatrix[0][0]);
		glUniformMatrix4fv(skyboxModelMatrixIDma, 1, GL_FALSE, &glm::mat4(1.0f)[0][0]);
		glUniform3f(shaderLightColourIDma, 0, 0, 0);


		skybox.render();

		
		

		//square.draw();
		glUseProgram(0);
		newInput.inputQueue();
		osInterface.swapBuffer();
	}

	return 0;
	
}
