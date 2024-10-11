#pragma once
#include <string>

namespace Gameplay
{
    namespace Cell
    {
        enum class CellState
        {
            HIDDEN,
            OPEN,
            FLAGGED,
        };

        enum class CellAction
        {
            OPEN_CELL,
            FLAG_CELL,
        };

        enum class CellValue
        {
            EMPTY,
            ONE,
            TWO,
            THREE,
            FOUR,
            FIVE,
            SIX,
            SEVEN,
            EIGHT,
            MINE,
        };

        inline char CellValueToString(CellValue value)
        {
            switch (value)
            {
            case::Gameplay::Cell::CellValue::EMPTY:
                return ' ';
            case::Gameplay::Cell::CellValue::ONE:
                return '1';
            case::Gameplay::Cell::CellValue::TWO:
                return '2';
            case::Gameplay::Cell::CellValue::THREE:
                return '3';
            case::Gameplay::Cell::CellValue::FOUR:
                return '4';
            case::Gameplay::Cell::CellValue::FIVE:
                return '5';
            case::Gameplay::Cell::CellValue::SIX:
                return '6';
            case::Gameplay::Cell::CellValue::SEVEN:
                return '7';
            case::Gameplay::Cell::CellValue::EIGHT:
                return '8';
            case::Gameplay::Cell::CellValue::MINE:
                return '*';
            default:
                return ' ';
            }
        }

        class CellModel
        {
        private:
            CellState cell_state;
            CellValue cell_value;

            int row_position;
            int column_position;

        public:
            CellModel(int row, int column);
            ~CellModel();

            CellState getCellState() const;
            void setCellState(CellState state);

            CellValue getCellValue() const;
            void setCellValue(CellValue value);

            int getCellRowPosition() const;
            void setCellRowPosition(int position);

            int getCellColumnPosition() const;
            void setCellColumnPosition(int position);

            void reset();
        };

    }
}