#pragma once
#include "../../header/Global/ServiceLocator.h"

namespace Main
{
	class GameService
	{
	private:
		Global::ServiceLocator* service_locator;

		void initialize();
		void destroy();

	public:
		GameService();
		virtual ~GameService();

		void ignite();
		void update();
		void render();
		bool isRunning();
	};
}