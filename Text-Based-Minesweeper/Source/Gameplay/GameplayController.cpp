#include "../../header/Gameplay/GameplayController.h"
#include "../../header/Main/GameService.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Time/TimeService.h"
#include <iostream>

namespace Gameplay
{
	using namespace Global;
	using namespace Time;
	using namespace Main;
	using namespace std;

	GameplayController::GameplayController()
	{
	}

	GameplayController::~GameplayController() {}

	void GameplayController::initialize()
	{
		resetGame();
	}

	void GameplayController::startGame()
	{
		showRules();
		char choice;
		cin >> choice;
		if (choice == 'Y' || choice == 'y') 
		{
			beginGame();
		}
		else 
		{
			setGameStatus(GameStatus::ENDED);
			cout << "Game closed.\n";
		}
	}

	void GameplayController::showRules()
	{
		cout << "---------------------------------------------\n";
		cout << "|          WELCOME TO MINESWEEPER GAME       |\n";
		cout << "---------------------------------------------\n";
		cout << "\nRULES:\n";
		cout << "1. The board is divided into cells, with mines randomly distributed.\n";
		cout << "2. To win, you need to open all the cells.\n";
		cout << "3. The number on a cell shows the number of mines adjacent to it. Using this information, you can determine\n";
		cout << "   cells that are safe, and cells that contain mines.\n";
		cout << "4. Interact, evolve and enjoy!\n";
		cout << "\nHow to Play:\n";
		cout << "1. User will input x & y (coordinates where they want to click).\n";
		cout << "2. In each step, check for win or lose case.\n";
		cout << "\nTake n*n (n >= 9 && n<= 20)\n";
		cout << "\nEnter Y/y to continue or any other key to close the game\n";
	}

	void GameplayController::update()
	{
		updateRemainingTime();

		if (isTimeOver() && game_result == GameResult::NONE)
		{
			endGame(GameResult::LOST);
		}
	}

	void GameplayController::updateRemainingTime()
	{
		if (game_status == GameStatus::STARTED)
		{
			remaining_time -= ServiceLocator::getInstance()->getTimeService()->getDeltaTime();
			cout << "Remaining Time: " << remaining_time << endl;
		}
	}

	void GameplayController::render()
	{
		// Yet to implement
	}

	bool GameplayController::isTimeOver()
	{
		if (remaining_time <= 0) 
		{
			remaining_time = 0;
			cout << "------------------TIME OUT-------------------\n";
			return true;
		}
		else
		{
			return false;
		}
	}

	void GameplayController::gameLost()
	{
		setGameResult(GameResult::LOST);
	}

	void GameplayController::gameWon()
	{
		setGameResult(GameResult::WON);
	}

	void GameplayController::beginGame()
	{
		do
		{
			cout << "Enter the number of cells in a row: ";
			cin >> number_of_rows;
			if (number_of_rows < 9 || number_of_rows>20)
			{
				cout << "Numbers are out of range. Take n*n (n >= 9 && n<= 20).\n";
			}
		} while (number_of_rows < 9 || number_of_rows>20);
		numnber_of_columns = number_of_rows;
		cout << "---------------------------------------------\n";
		cout << "|                GAME STARTS                |\n";
		cout << "---------------------------------------------\n";
		resetGame();
		ServiceLocator::getInstance()->getTimeService()->updatePreviousTime();
		setGameStatus(GameStatus::STARTED);
	}

	void GameplayController::showResults()
	{
		if (game_result == GameResult::LOST)
		{
			cout << "---------------------------------------------\n";
			cout << "|                   YOU LOSE                |\n";
			cout << "---------------------------------------------\n";
		}
		else if (game_result == GameResult::WON)
		{
			cout << "---------------------------------------------\n";
			cout << "|                   YOU WIN                 |\n";
			cout << "---------------------------------------------\n";
		}
	}

	void GameplayController::endGame(GameResult result)
	{
		setGameStatus(GameStatus::ENDED);
		switch (result)
		{
		case GameResult::WON:
			gameWon();
			break;
		case GameResult::LOST:
			gameLost();
			break;
		default:
			break;
		}
		showResults();
	}

	void GameplayController::resetGame()
	{
		game_status = GameStatus::NONE;
		game_result = GameResult::NONE;
		remaining_time = max_level_duration;
	}

	bool GameplayController::isGameOver() const
	{
		return (game_status == GameStatus::ENDED);
	}

	float GameplayController::getRemainingTime() const
	{
		return remaining_time;
	}

	int GameplayController::getMinesCount() const
	{
		return 0;
	}

	GameStatus GameplayController::getGameStatus() const
	{
		return game_status;
	}

	void GameplayController::setGameStatus(GameStatus result)
	{
		game_status = result;
	}

	GameResult GameplayController::getGameResult() const
	{
		return game_result;
	}

	void GameplayController::setGameResult(GameResult result)
	{
		game_result = result;
	}
}