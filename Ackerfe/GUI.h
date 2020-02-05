#pragma once
#include <glm-0.9.9.7/glm/glm.hpp>
#include <SDL/SDL_events.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>

namespace Ackerfe {
	class GUI
	{
		static CEGUI::OpenGL3Renderer* mGUIRenderer;
		CEGUI::GUIContext* mContext = nullptr;
		CEGUI::Window* mRoot = nullptr;
		unsigned int mPreviousTime = 0;
		int mGet_fX, mGetfY;

	public:
		void init(std::string& resourceDirectory);
		void destroy();
		void update();
		void render();

		void setMouseCursor(const std::string &imageFile);
		void showMouseCursor();
		void hideMouseCursor();

		void keyUpFunc(SDL_Event &keyEvent);
		void keyDownFunc(SDL_Event &keyEvent);
		void mouseMotionFunc(SDL_Event &motionEvent);
		void decodeInputText(SDL_Event &textEvent);
		void mouseButtonDownFunc(SDL_Event &buttonEvent);
		void mouseButtonUpFunc(SDL_Event &buttonEvent);
		
		
		static CEGUI::OpenGL3Renderer* getRenderer() { return mGUIRenderer; }

		const CEGUI::GUIContext* getContext() { return mContext; }

		void loadScheme(const std::string &schemeFile);
		void setFont(const std::string &fontFile);

		CEGUI::Window* createWidget(const std::string &scheme, const glm::vec4 &percRect, const glm::vec4 &pixRect, const std::string &name);
		static void setWidgetRect(CEGUI::Window* widget, const glm::vec4 &percRect, const glm::vec4 &pixRect);

	};
}
