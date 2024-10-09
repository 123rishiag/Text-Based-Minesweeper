#include "../../../header/Gameplay/Board/BoardController.h"
#include "../../../header/Gameplay/Cell/CellController.h"
#include "../../../header/Gameplay/GameplayController.h"
#include "../../../header/Gameplay/Cell/CellModel.h"
#include "../../../header/Global/ServiceLocator.h"

namespace Gameplay
{
	namespace Board
	{
		using namespace Global;
		using namespace Cell;

		BoardController::BoardController() : random_engine(random_device()) //// Seeded random engine with random device
		{
			// Setting up default sizes
			number_of_rows = selected_number_of_rows;
			number_of_columns = selected_number_of_columns;
			mines_count = selected_mines_count;

			resizeVector();
		}

		BoardController::~BoardController()
		{
			destroy();
		}

		void BoardController::createBoard()
		{
			for (int row = 0; row < number_of_rows; row++)
			{
				for (int column = 0; column < number_of_columns; column++)
				{
					board[row][column] = new CellController(row, column); //Passing Cell Index in Cell Controller's constructor
				}
			}
		}

		void BoardController::initialize()
		{
			reset();
		}

		void BoardController::update()
		{
		}

		void BoardController::render()
		{
		}

		void BoardController::processCellInput(Cell::CellController* cell_controller)
		{
			if (board_state == BoardState::COMPLETED)
				return; // Returning doesn't allow processing input and hence input is disabled

			openCell(cell_controller->getCellRowPosition(), cell_controller->getCellColumnPosition());
		}

		void BoardController::populateBoard(int row, int column)
		{
			populateMines(row, column);
			populateCells();
		}

		void BoardController::populateMines(int row, int column)
		{
			// Co-ordinate distribution i.e. selecting random position for mines.
			std::uniform_int_distribution<int> x_distribution(0, number_of_rows - 1); //Subtracted -1 because index in an array ranges from 0 to size-1
			std::uniform_int_distribution<int> y_distribution(0, number_of_columns - 1);

			for (int mine = 0; mine < mines_count; mine++)
			{
				int i = static_cast<int>(x_distribution(random_engine));
				int j = static_cast<int>(y_distribution(random_engine));

				// If the cell is already a mine or it's the same cell that the player wants to open --> Run the loop an extra time
				if (board[i][j]->getCellValue() == CellValue::MINE || (row == i && column == j))
				{
					mine--; // mine-- runs a loop 1 extra time
				}
				else
				{
					board[i][j]->setCellValue(CellValue::MINE);
				}
			}
		}

		void BoardController::populateCells()
		{
			for (int a = 0; a < number_of_rows; a++)
			{
				for (int b = 0; b < number_of_columns; b++)
				{
					if (board[a][b]->getCellValue() != CellValue::MINE)
					{
						CellValue value = static_cast<CellValue>(countMinesAround(a, b));
						board[a][b]->setCellValue(value);
					}
				}
			}
		}

		int BoardController::countMinesAround(int row, int column) const
		{
			int mines_around = 0;

			for (int a = -1; a < 2; a++)
			{
				for (int b = -1; b < 2; b++)
				{
					//If its the current cell, or cell position is not valid, then the loop will skip once
					if ((a == 0 && b == 0) || !isValidCellPosition((row + a), (column + b))) continue;

					if (board[a + row][b + column]->getCellValue() == CellValue::MINE) mines_around++;
				}
			}

			return mines_around;
		}

		void BoardController::flagCell(int row, int column)
		{
			switch (board[row][column]->getCellState())
			{
			case::Gameplay::Cell::CellState::FLAGGED:
				flagged_cells--; //Used to update Gameplay UI
				break;
			case::Gameplay::Cell::CellState::HIDDEN:
				flagged_cells++; //Used to update Gameplay UI
				break;
			}

			board[row][column]->flagCell();
		}

		void BoardController::openCell(int row, int column)
		{
			if (board[row][column]->canOpenCell())
			{
				if (board_state == BoardState::FIRST_CELL)
				{
					populateBoard(row, column);
					board_state = BoardState::PLAYING;
				}
				processCellValue(row, column); //Handles different cell value
				board[row][column]->openCell();

				if (areAllCellOpen())
					ServiceLocator::getInstance()->getGameplayService()->endGame(GameResult::WON);
			}
		}

		void BoardController::flagAllMines()
		{
			for (int row = 0; row < number_of_rows; row++)
			{
				for (int col = 0; col < number_of_columns; col++)
				{
					if (board[row][col]->getCellValue() == CellValue::MINE && board[row][col]->getCellState() != CellState::FLAGGED)
						flagCell(row, col);
				}
			}
		}

		void BoardController::processCellValue(int row, int column)
		{
			switch (board[row][column]->getCellValue())
			{
			case::Gameplay::Cell::CellValue::EMPTY:
				processEmptyCell(row, column); //Handles everything related to opening empty cells
				break;
			case::Gameplay::Cell::CellValue::MINE:
				processMineCell(row, column);
				break;
			default:
				break;
			}
		}

		void BoardController::processEmptyCell(int row, int column)
		{
			openEmptyCells(row, column);
		}

		void BoardController::processMineCell(int row, int column)
		{
			ServiceLocator::getInstance()->getGameplayService()->endGame(GameResult::LOST);
		}

		void BoardController::openEmptyCells(int row, int column)
		{
			// Check the state of the cell at the given position.
			switch (board[row][column]->getCellState())
			{
				// If the cell is already OPEN, no further action is required, and we return from the function.
			case::Gameplay::Cell::CellState::OPEN:
				return;

				// If the cell is FLAGGED, decrement the flagged_cells count as the flag will be removed.
			case::Gameplay::Cell::CellState::FLAGGED:
				flagged_cells--;
				// No break statement here, so the default case will execute next

			// Default case handles the scenario where the cell is neither OPEN nor FLAGGED, which implies it is HIDDEN.
			default:
				// Opens the cell at the current position.
				board[row][column]->openCell();
			}

			// Iterate over all neighbouring cells.
			for (int a = -1; a < 2; a++)
			{
				for (int b = -1; b < 2; b++)
				{
					// Skip the iteration if it's the current cell or if the new cell position is not valid.
					if ((a == 0 && b == 0) || !isValidCellPosition((row + a), (column + b)))
						continue;

					// Calculate the position of the neighbouring cell.
					openCell((row + a), (column + b));
				}
			}
		}

		void BoardController::openAllCells()
		{
			for (int row = 0; row < number_of_rows; row++)
			{
				for (int column = 0; column < number_of_columns; column++)
				{
					board[row][column]->openCell();
				}
			}
		}

		bool BoardController::isValidCellPosition(int row, int column) const
		{
			// if position is withing the bounds of the array, then position is valid
			return (row >= 0 && column >= 0 && row < number_of_rows && column < number_of_columns);
		}

		bool BoardController::areAllCellOpen()
		{
			int total_cell_count = number_of_rows * number_of_columns;
			int open_cell_count = 0;

			for (int a = 0; a < number_of_rows; a++)
			{
				for (int b = 0; b < number_of_columns; b++)
				{
					if (board[a][b]->getCellState() == CellState::OPEN)
					{
						open_cell_count++;
					}
				}
			}

			return (total_cell_count - open_cell_count == mines_count);
		}

		void BoardController::showBoard()
		{
			switch (board_state)
			{
			case Gameplay::Board::BoardState::FIRST_CELL:
				populateBoard(0, 0);
				openAllCells();
				break;
			case Gameplay::Board::BoardState::PLAYING:
				openAllCells();
				break;
			case Gameplay::Board::BoardState::COMPLETED:
				break;
			default:
				break;
			}
		}

		void BoardController::reset()
		{
			// Delete previous board
			deleteBoard();

			// Set up new size for the game
			number_of_rows = selected_number_of_rows;
			number_of_columns = selected_number_of_columns;
			mines_count = selected_mines_count;
			board_state = BoardState::FIRST_CELL;
			flagged_cells = 0;

			// Resizing the vector
			resizeVector();
			createBoard(); // Recreating board with new sizes
			resetBoard(); // Reseting the cell views
		}

		void BoardController::resetBoard()
		{
			// Reseting each cell as needed
			for (int row = 0; row < number_of_rows; row++)
			{
				for (int column = 0; column < number_of_columns; column++)
				{
					board[row][column]->reset();
				}
			}
		}

		void BoardController::deleteBoard()
		{
			for (int row = 0; row < number_of_rows; row++)
			{
				for (int column = 0; column < number_of_columns; column++)
				{
					delete(board[row][column]);
				}
			}
		}

		void BoardController::resizeVector()
		{
			// Resize the outer vector to the desired number of rows
			board.resize(number_of_rows);

			// Resize each inner vector to the desired number of columns
			for (int row = 0; row < number_of_rows; row++)
			{
				board[row].resize(number_of_columns, nullptr);
			}
		}

		int BoardController::getSelectedRowsCount() const
		{
			return selected_number_of_rows;
		}

		void BoardController::setSelectedRowsCount(int count)
		{
			selected_number_of_rows = count;
		}

		int BoardController::getSelectedColumnsCount() const
		{
			return selected_number_of_columns;
		}

		void BoardController::setSelectedColumnsCount(int count)
		{
			selected_number_of_columns = count;
		}

		int BoardController::getSelectedMinesCount() const
		{
			return selected_mines_count;
		}

		void BoardController::setSelectedMinesCount(int count)
		{
			selected_mines_count = count;
		}

		int BoardController::getRowsCount() const
		{
			return number_of_rows;
		}

		int BoardController::getColumnsCount() const
		{
			return number_of_columns;
		}

		int BoardController::getMinesCount() const
		{
			return mines_count - flagged_cells;
		}

		BoardState BoardController::getBoardState() const
		{
			return board_state;
		}

		void BoardController::setBoardState(BoardState state)
		{
			board_state = state;
		}

		void BoardController::destroy()
		{
			deleteBoard();
		}
	}
}