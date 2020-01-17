#pragma once
#include "IAppState.h"
namespace Ackerfe {
	class LogoState : public IAppState
	{
	public:
		LogoState();
		~LogoState();

		void update();
		void render();
	};
}
