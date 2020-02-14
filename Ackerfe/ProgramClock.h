#pragma once
#include "OSInterface.h"

namespace Ackerfe
{

	class ProgramClock
	{
	public:
		ProgramClock();
		~ProgramClock();

		void set();

		unsigned int getDeltaTime();

		unsigned int getSet();

		unsigned int getProgramUpTime();

	private:
		unsigned int mPreviousTime;
	};

}