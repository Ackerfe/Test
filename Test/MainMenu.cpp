#include "MainMenu.h"
#include "Spritefont.h"
#include "ImageLoad.h"
#include "SimpleShader.h"

void MainMenu::init(Ackerfe::GraphicsResourceManager * GRM,
	std::string vertShader, std::string fragShader,
	int screenWidth, int screenHeight,
	glm::vec2 cameraPosition, float cameraZoom,
	Ackerfe::WindowHandler* window, Ackerfe::GUI* gui, Ackerfe::InputHandler* input)
{
	mGRM = GRM;
	mProgramID = Ackerfe::compileLinkSimpleShaders(vertShader, fragShader);
	mPerspectiveUniformID = glGetUniformLocation(mProgramID, "Perspective");
	mCamera.init(screenWidth, screenHeight, cameraPosition, cameraZoom);
	mOrthoMatrix = mCamera.getMatrix();
	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;
	mWindow = window;
	mGUI = gui;
	mInput = input;
	
}

void MainMenu::mainMenuLoop()
{
	mGRM->mMultisprite2D.removeBackSprites(3);

	
	mGUI->loadScheme("TaharezLook.scheme");
	mGUI->setFont("DejaVuSans-10");

	//mGUI->setMouseCursor("TaharezLook/MouseArrow");
	//mGUI->showMouseCursor();
	
	
	CEGUI::PushButton* startButton = (CEGUI::PushButton*)mGUI->createWidget("TaharezLook/Button", glm::vec4(0.45f, 0.4f, 0.1f, 0.05f), glm::vec4(0.0f), "StartButton");
	startButton->setText("Start");
	startButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenu::beginGame, this));


	CEGUI::PushButton* exitButton = (CEGUI::PushButton*)mGUI->createWidget("TaharezLook/Button", glm::vec4(0.45f, 0.5f, 0.1f, 0.05f), glm::vec4(0.0f), "ExitButton");
	exitButton->setText("Exit");
	exitButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenu::exitGame, this));

	CEGUI::PushButton* testButton = (CEGUI::PushButton*)mGUI->createWidget("TaharezLook/Button", glm::vec4(0.45f, 0.6f, 0.1f, 0.05f), glm::vec4(0.0f), "TestButton");
	testButton->setText("Test");

	CEGUI::Combobox* textBox = static_cast<CEGUI::Combobox*>(mGUI->createWidget("TaharezLook/Combobox", glm::vec4(0.45f, 0.7f, 0.1f, 0.05f), glm::vec4(0.0f), "Typebox"));

	GLuint backGroundTextureID = Ackerfe::loadPng("Texture/LogoState/LogoBackground.png");
	GLuint sprite1 = Ackerfe::loadPng("Texture/Main Menu/Asteroid1.png");
	GLuint sprite2 = Ackerfe::loadPng("Texture/Main Menu/Asteroid2.png");

	float fifthScreenWidth = mScreenWidth / 5.0f;
	float fifthScreenHeight = mScreenHeight / 5.0f;
	float twoFifthsScreenWidth = fifthScreenWidth * 2.0f;
	float twoFifthsScreenHeight = fifthScreenHeight * 2.0f;

	mGRM->mMultisprite2D.addSprite(backGroundTextureID, 0.0f,
		Ackerfe::Vertex(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(0.0f, mScreenHeight, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(mScreenWidth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(mScreenWidth, mScreenHeight, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)));

	mGRM->mMultisprite2D.addSprite(sprite1, 0.0f,
		Ackerfe::Vertex(fifthScreenWidth, fifthScreenHeight, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(fifthScreenWidth, twoFifthsScreenHeight, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(twoFifthsScreenWidth, fifthScreenHeight, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(twoFifthsScreenWidth, twoFifthsScreenHeight, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)));

	mGRM->mMultisprite2D.addSprite(sprite2, 0.0f,
		Ackerfe::Vertex(twoFifthsScreenWidth + fifthScreenWidth, fifthScreenHeight, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(twoFifthsScreenWidth + fifthScreenWidth, twoFifthsScreenHeight, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(2.0f*twoFifthsScreenWidth, fifthScreenHeight, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)),
		Ackerfe::Vertex(2.0f*twoFifthsScreenWidth, twoFifthsScreenHeight, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, Ackerfe::ColourRGBA8(255, 255, 255, 255)));

	Ackerfe::SpriteFont spriteFont("Fonts/ThreSixt_2.ttf", 64);

	char buffer[256];
	sprintf_s(buffer, "Asteroids!");
	spriteFont.draw(mGRM->mMultisprite2D, buffer, glm::vec2(twoFifthsScreenWidth, mScreenHeight-fifthScreenHeight), glm::vec2(1.0f), 0.0f, Ackerfe::ColourRGBA8(255, 100, 100, 255));

	glDisable(GL_DEPTH_TEST);

	mGRM->mMultisprite2D.prepareBatches();

	Ackerfe::AAudio audio;
	audio.init();
	std::string soundString = "SoundEffects/Music/IWasTheSun.mp3";
	audio.loadSound(soundString, true);
	int audioFlag = 0;

	
	while (!mStartGame)
	{
		if (audioFlag == 0)
		{
			audio.play(soundString);
			audioFlag = 1;
		}

		mInput->inputQueue();
		render();
		mGUI->update();
	}
	
	glEnable(GL_DEPTH_TEST);
}

void MainMenu::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(mProgramID);

	glUniformMatrix4fv(mPerspectiveUniformID, 1, GL_FALSE, &mOrthoMatrix[0][0]);

	mGRM->mMultisprite2D.renderBatches();

	mGUI->render();

	glUseProgram(0);

	mWindow->swapBuffer();
}

bool MainMenu::exitGame(const CEGUI::EventArgs & e)
{
	SDL_QUIT;
	exit(0);
	return false;
}

bool MainMenu::beginGame(const CEGUI::EventArgs & e)
{
	mStartGame = true;
	return true;
}
