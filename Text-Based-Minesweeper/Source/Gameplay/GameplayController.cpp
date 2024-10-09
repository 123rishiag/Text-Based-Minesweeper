#include "../../header/Gameplay/GameplayController.h"
#include "../../header/Main/GameService.h"
#include "../../header/Global/ServiceLocator.h"
#include <iostream>
#include <sstream>

namespace Gameplay
{
	using namespace Global;
	using namespace Main;
	using namespace std;

	GameplayController::GameplayController()
	{
		board_service = nullptr;
	}

	GameplayController::~GameplayController() {}

	void GameplayController::initialize()
	{
		board_service = ServiceLocator::getInstance()->getBoardService();
		resetGame();
	}

	void GameplayController::startGame()
	{
		showRules();
		char choice;
		cin >> choice;
		if (choice == 'Y' || choice == 'y') 
		{
			runGame();
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
		cout << "\nTake n*n (n >= " << min_cell_threshold << " && n <= " << max_cell_threshold << ")\n";
		cout << "\nEnter Y/y to continue or any other key to close the game\n";
	}

	void GameplayController::runGame()
	{
		do
		{
			cout << "Enter the number of cells in a row: ";
			cin >> number_of_rows;
			if (number_of_rows < min_cell_threshold || number_of_rows>max_cell_threshold)
			{
				cout << "Numbers are out of range. Take n*n (n >= " << min_cell_threshold << " && n <= " << max_cell_threshold << ").\n";
			}
		} while (number_of_rows < min_cell_threshold || number_of_rows>max_cell_threshold);
		numnber_of_columns = number_of_rows;
		calculateMines();
		cout << "---------------------------------------------\n";
		cout << "|                GAME STARTS                |\n";
		cout << "---------------------------------------------\n";

		setGameStatus(GameStatus::STARTED);
		board_service->resetBoard(number_of_rows, numnber_of_columns, number_of_mines);
		startGameLoop();
	}

	void GameplayController::startGameLoop()
	{
		string position;
		// Clear the newline character left in the input stream
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		while (game_status != GameStatus::ENDED)
		{
			cout << "Enter x and y coordinates (space separated): ";
			getline(cin, position);

			vector<int> coordinates = parsePosition(position);
			if (coordinates.size() != 2)
			{
				cout << "Error: Please enter exactly two space-separated integers.\n";
				continue;
			}

			int x = coordinates[0];
			int y = coordinates[1];

			if (x < 0 || x >= number_of_rows || y < 0 || y >= numnber_of_columns)
			{
				cout << "Error: Coordinates out of range. Valid range is (0,0) to ("
					<< number_of_rows - 1 << "," << numnber_of_columns - 1 << ").\n";
				continue;
			}

			cout << "ok\n";
		}
	}

	vector<int> GameplayController::parsePosition(const string& input)
	{
		vector<int> result;
		stringstream ss(input);
		int value;

		// Extract integers from the input string
		while (ss >> value) {
			result.push_back(value);
		}

		return result;
	}


	void GameplayController::update() { }

	void GameplayController::render()
	{
		// Yet to implement
	}

	void GameplayController::calculateMines()
	{
		int totalCells = number_of_rows * numnber_of_columns;
		number_of_mines = std::max(1, static_cast<int>(totalCells * 0.15)); // At most around 15% of cells are mines
	}

	void GameplayController::gameLost()
	{
		setGameResult(GameResult::LOST);
	}

	void GameplayController::gameWon()
	{
		setGameResult(GameResult::WON);
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
		number_of_rows = 0;
		numnber_of_columns = 0;
		number_of_mines = 0;
	}

	bool GameplayController::isGameOver() const
	{
		return (game_status == GameStatus::ENDED);
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