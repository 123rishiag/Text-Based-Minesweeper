#include "../../../header/Gameplay/Cell/CellModel.h"

namespace Gameplay
{
	namespace Cell
	{
		CellModel::CellModel(int row, int column)
		{
			row_position = row;
			column_position = column;
		}

		CellModel::~CellModel() = default;

		CellState CellModel::getCellState() const
		{
			return cell_state;
		}

		void CellModel::setCellState(CellState state)
		{
			cell_state = state;
		}

		CellValue CellModel::getCellValue() const
		{
			return cell_value;
		}

		void CellModel::setCellValue(CellValue value)
		{
			cell_value = value;
		}

		int CellModel::getCellRowPosition() const
		{
			return row_position;
		}

		void CellModel::setCellRowPosition(int position)
		{
			row_position = position;
		}

		int CellModel::getCellColumnPosition() const
		{
			return column_position;
		}

		void CellModel::setCellColumnPosition(int position)
		{
			column_position = position;
		}

		void CellModel::reset()
		{
			cell_state = CellState::HIDDEN;
			cell_value = CellValue::EMPTY;
		}
	}
}