#include "../../../header/Gameplay/Board/BoardService.h"
#include "../../../header/Gameplay/Board/BoardController.h"

namespace Gameplay
{
	namespace Board
	{
		using namespace Cell;

		BoardService::BoardService()
		{
			board_controller = nullptr;
		}

		BoardService::~BoardService()
		{
			destroy();
		}

		void BoardService::initialize()
		{
			board_controller = new BoardController();
			board_controller->initialize();
		}

		void BoardService::update()
		{
			board_controller->update();
		}

		void BoardService::render()
		{
			board_controller->render();
		}

		void BoardService::flagAllMines()
		{
			board_controller->flagAllMines();
		}

		void BoardService::processCellInput(int row, int column, CellAction action)
		{
			board_controller->processCellInput(row, column, action);
		}

		void BoardService::displayGrid()
		{
			board_controller->displayGrid();
		}

		void BoardService::showBoard()
		{
			board_controller->showBoard();
		}

		void BoardService::resetBoard()
		{
			board_controller->reset();
		}

		void BoardService::resetBoard(int rows, int columns, int mines)
		{
			board_controller->setSelectedRowsCount(rows);
			board_controller->setSelectedColumnsCount(columns);
			board_controller->setSelectedMinesCount(mines);
			resetBoard();
		}

		int BoardService::getSelectedRowsCount() const
		{
			return board_controller->getSelectedRowsCount();
		}

		int BoardService::getSelectedColumnsCount() const
		{
			return board_controller->getSelectedColumnsCount();
		}

		int BoardService::getSelectedMinesCount() const
		{
			return board_controller->getSelectedMinesCount();
		}

		int BoardService::getMinesCount() const
		{
			return board_controller->getMinesCount();
		}

		BoardState BoardService::getBoardState() const
		{
			return board_controller->getBoardState();
		}

		void BoardService::setBoardState(BoardState state)
		{
			board_controller->setBoardState(state);
		}

		void BoardService::destroy()
		{
			delete(board_controller);
		}
	}
}