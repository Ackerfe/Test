#pragma once
namespace Ackerfe
{
	class IAppState
	{
	public:
		IAppState() {};
		virtual ~IAppState() {};
		virtual void update() = 0;
		virtual void render() = 0;

	};
}
