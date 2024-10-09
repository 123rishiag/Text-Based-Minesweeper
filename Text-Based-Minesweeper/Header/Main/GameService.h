#pragma once
#include "../../header/Global/ServiceLocator.h"

namespace Main
{
	enum class GameState
	{
		BOOT,
		GAMEPLAY,
	};

	class GameService
	{
	private:
		static GameState current_state;
		Global::ServiceLocator* service_locator;

		void initialize();
		void startGameplay();
		void destroy();

	public:
		GameService();
		virtual ~GameService();

		void ignite();
		void update();
		void render();
		bool isRunning();

		static void setGameState(GameState new_state);
		static GameState getGameState();
	};
}