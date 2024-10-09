#pragma once

namespace Gameplay
{
	enum class GameStatus
	{
		NONE,
		STARTED,
		ENDED,
	};

	enum class GameResult
	{
		NONE,
		WON,
		LOST
	};

	namespace Board
	{
		class BoardService;
	}

	class GameplayController
	{
	private:
		const float max_level_duration = 3.f;
		float remaining_time;

		int number_of_rows;
		int numnber_of_columns;

		GameStatus game_status = GameStatus::NONE;
		GameResult game_result = GameResult::NONE;
		void showRules();
		void updateRemainingTime();
		bool isTimeOver();
		void gameLost();
		void gameWon();
		void beginGame();
		void showResults();

	public:
		GameplayController();
		~GameplayController();

		void initialize();
		void update();
		void render();

		void startGame();
		void endGame(GameResult result);
		void resetGame();

		bool isGameOver() const;
		float getRemainingTime() const;
		int getMinesCount() const;
		GameStatus getGameStatus() const;
		void setGameStatus(GameStatus status);
		GameResult getGameResult() const;
		void setGameResult(GameResult result);
	};
}