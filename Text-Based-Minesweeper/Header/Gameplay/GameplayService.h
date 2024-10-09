#pragma once

namespace Gameplay
{
	class GameplayController;

	enum class GameResult;

	class GameplayService
	{
	private:
		GameplayController* gameplay_controller;

		void destroy();

	public:
		GameplayService();
		~GameplayService();

		void initialize();
		void update();
		void render();
		void startGame();
		void endGame(GameResult result);

		bool isGameOver() const;
		GameResult getGameResult() const;
	};
}