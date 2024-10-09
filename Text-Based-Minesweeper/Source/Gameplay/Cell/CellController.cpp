#include "../../../header/Gameplay/Cell/CellController.h"
#include "../../../header/Gameplay/Cell/CellModel.h"
#include "../../../header/Global/ServiceLocator.h"

namespace Gameplay
{
	namespace Cell
	{
		using namespace Global;

		CellController::CellController(int row, int column)
		{
			cell_model = new CellModel(row, column);
		}

		CellController::~CellController()
		{
			destroy();
		}

		void CellController::initialize() { }

		void CellController::update() { }

		void CellController::render() {	}

		CellState CellController::getCellState() const
		{
			return cell_model->getCellState();
		}

		void CellController::setCellState(CellState state)
		{
			cell_model->setCellState(state);
		}

		CellValue CellController::getCellValue() const
		{
			return cell_model->getCellValue();
		}

		void CellController::setCellValue(CellValue value)
		{
			cell_model->setCellValue(value);
		}

		int CellController::getCellRowPosition() const
		{
			return cell_model->getCellRowPosition();
		}

		void CellController::setCellRowPosition(int position)
		{
			cell_model->setCellRowPosition(position);
		}

		int CellController::getCellColumnPosition() const
		{
			return cell_model->getCellColumnPosition();
		}

		void CellController::setCellColumnPosition(int position)
		{
			cell_model->setCellColumnPosition(position);
		}

		void CellController::reset()
		{
			cell_model->reset();
		}

		void CellController::openCell()
		{
			cell_model->setCellState(CellState::OPEN);
		}

		bool CellController::canOpenCell()
		{
			return cell_model->getCellState() != CellState::FLAGGED && cell_model->getCellState() != CellState::OPEN;
		}

		void CellController::flagCell()
		{
			switch (cell_model->getCellState())
			{
			case::Gameplay::Cell::CellState::FLAGGED:
				cell_model->setCellState(CellState::HIDDEN);
				break;
			case::Gameplay::Cell::CellState::HIDDEN:
				cell_model->setCellState(CellState::FLAGGED);
				break;
			}
		}

		void CellController::destroy()
		{
			delete (cell_model);
		}
	}
}