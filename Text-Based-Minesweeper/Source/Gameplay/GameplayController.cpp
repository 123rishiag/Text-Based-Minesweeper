#include "../../header/Gameplay/GameplayController.h"
#include "../../header/Gameplay/Board/BoardController.h"
#include "../../header/Gameplay/Cell/CellModel.h"
#include "../../header/Main/GameService.h"
#include "../../header/Global/ServiceLocator.h"
#include <iostream>
#include <sstream>

namespace Gameplay
{
	using namespace Global;
	using namespace Board;
	using namespace Cell;
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
		cout << "2. To win, you need to open all the cells without triggering any mine.\n";
		cout << "3. The number on a cell shows the number of mines adjacent to it. Using this information, you can determine\n";
		cout << "   cells that are safe, and cells that contain mines.\n";
		cout << "4. You can flag cell, if you have doubts on any cell that it may contain mine doing which you won't be able to";
		cout << " open the cell. To open you have to unflag the cell.\n";
		cout << "5. Interact, evolve and enjoy!\n";
		cout << "\nHow to Play:\n";
		cout << "1. User will input x & y (coordinates where they want to click).\n";
		cout << "2. In each step, check for win or lose case.\n";
		cout << "\nTake n*n (n >= " << min_cell_threshold << " && n <= " << max_cell_threshold << ")\n";
		cout << "\nHow to Play: \n1. Enter coordinates (space separated) to open cell. Example - 5 10";
	    cout << "\n2. Enter coordinates and then 'F' (space separated) to flag cell. Example - 5 10 F\n";
		cout << "\nSymbols:\n'+' - Unopened Cell \n'F' - Flagged Cell \n'*' - Mine Cell \n' ' - Blank Cell\n";
		cout << "\nEnter Y/y to continue or any other key to close the game: ";
	}

	void GameplayController::runGame()
	{
		do
		{
			cout << "\nEnter the number of cells in a row: ";
			cin >> number_of_rows;
			if (number_of_rows < min_cell_threshold || number_of_rows>max_cell_threshold)
			{
				cout << "Numbers are out of range. Take n*n (n >= " << min_cell_threshold << " && n <= " << max_cell_threshold << ").\n";
			}
		} while (number_of_rows < min_cell_threshold || number_of_rows>max_cell_threshold);
		numnber_of_columns = number_of_rows;
		calculateMines(); // Setting up the mines based on rows inserted.

		cout << "\n";
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

		board_service->displayGrid();

		while (game_status != GameStatus::ENDED)
		{
			cout << "Enter x and y coordinates between 0 and " << number_of_rows - 1 << " (space separated) or coordinates followed by 'F' to flag: ";
			getline(cin, position);

			vector<string> coordinates = parsePosition(position);
			if (!(coordinates.size() == 3 && coordinates[2] == "F" || coordinates.size() == 2))
			{
				cout << "Error: Please enter exactly two space-separated integers or two space-separated integers followed by 'F' to flag.\n\n";
				continue;
			}

			int row, column;
			try 
			{
				row = stoi(coordinates[0]);
				column = stoi(coordinates[1]);
			}
			catch (invalid_argument&) 
			{
				cout << "Error: Please enter exactly two space-separated integers or two space-separated integers followed by 'F' to flag.\n\n";
				continue;
			}

			if (row < 0 || row >= number_of_rows || column < 0 || column >= numnber_of_columns)
			{
				cout << "Error: Coordinates out of range. Valid range is (0,0) to (" << number_of_rows - 1 << "," 
					<< numnber_of_columns - 1 << ").\n\n";
				continue;
			}

			if (coordinates.size() == 3 && coordinates[2] == "F")
			{
				board_service->processCellInput(row, column, CellAction::FLAG_CELL);
			}
			else
			{
				board_service->processCellInput(row, column, CellAction::OPEN_CELL);
			}
		}
	}

	vector<string> GameplayController::parsePosition(const string& input)
	{
		vector<string> result;
		stringstream ss(input);
		string token;

		// Extracting integers and any other tokens from the input string
		while (ss >> token) 
		{
			result.push_back(token);  // Store both numbers and characters as strings
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
		board_service->showBoard();
		board_service->setBoardState(BoardState::COMPLETED);
	}

	void GameplayController::gameWon()
	{
		setGameResult(GameResult::WON);
		board_service->flagAllMines();
		board_service->setBoardState(BoardState::COMPLETED);
	}

	void GameplayController::showResults()
	{
		if (game_result == GameResult::LOST)
		{
			cout << "\n";
			cout << "---------------------------------------------\n";
			cout << "|           MINE TRIGGERED! YOU LOSE        |\n";
			cout << "---------------------------------------------\n";
		}
		else if (game_result == GameResult::WON)
		{
			cout << "\n";
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