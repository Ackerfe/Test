#pragma once
#include <glm-0.9.9.7/glm/glm.hpp>
#include "OSInterface.h"
#include "CEGUI/CEGUI.h"
#include "CEGUI/RendererModules/OpenGL/GL3Renderer.h"
#include "MessagingSystem.h"
#include "ProgramClock.h"


namespace Ackerfe
{
	

	class GUI
	{
	public:
		GUI();
		~GUI();
		void init(const std::string &resourceDirectory, CorrespondentManager *corrManager, OSInterface * osInterface);
		void update();
		void destory();
		void render();

		void setMouseCursor(const std::string &imageFile);
		void showMouseCursor();
		void hideMouseCursor();

		void keyUpFunc(SDL_Event &evnt);
		void keyDownFunc(SDL_Event &evnt);
		void mouseMotionFunc(SDL_Event &evnt);
		void decodeInputText(SDL_Event &textEvent);
		void mouseButtonDownFunc(SDL_Event &evnt);
		void mouseButtonUPFunc(SDL_Event &evnt);


		static CEGUI::OpenGL3Renderer* getRenderer() {
			return mGUIRenderer;
		}
		const CEGUI::GUIContext* getContext() {
			return mContext;
		}

		void loadScheme(const std::string &schemeFile);
		void setFont(const std::string &fontFile);

		CEGUI::Window* createWidget(const std::string &scheme, const glm::vec4 &percRect, const glm::vec4 &pixRect, const std::string & name);
		static void setWidgetRect(CEGUI::Window* widget, const glm::vec4 &percRect, const glm::vec4 &pixRect);

	private:
		static CEGUI::OpenGL3Renderer* mGUIRenderer;
		CEGUI::GUIContext* mContext = nullptr;
		CEGUI::Window* mRoot = nullptr;
		OSInterface * mosInterface;
		ProgramClock mClock;
	};

}