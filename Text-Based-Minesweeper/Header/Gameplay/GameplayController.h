#pragma once
#include <vector>
#include <string>

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
		const float min_cell_threshold = 9;
		const float max_cell_threshold = 20;

		int number_of_rows;
		int numnber_of_columns;
		int number_of_mines;

		Board::BoardService* board_service;

		GameStatus game_status = GameStatus::NONE;
		GameResult game_result = GameResult::NONE;
		void showRules();
		void runGame();
		void startGameLoop();
		std::vector<int> parsePosition(const std::string& input);
		void calculateMines();
		void gameLost();
		void gameWon();
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
		GameStatus getGameStatus() const;
		void setGameStatus(GameStatus status);
		GameResult getGameResult() const;
		void setGameResult(GameResult result);
	};
}