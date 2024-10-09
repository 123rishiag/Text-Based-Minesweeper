#pragma once

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