#pragma once

namespace Gameplay
{
    namespace Cell
    {
        class CellModel;

        enum class CellState;
        enum class CellValue;

        class CellController
        {
        private:
            CellModel* cell_model;

            void destroy();

        public:
            CellController(int row, int column);
            ~CellController();

            void initialize();
            void update();
            void render();
            void reset();

            CellState getCellState() const;
            void setCellState(CellState state);

            CellValue getCellValue() const;
            void setCellValue(CellValue value);

            int getCellRowPosition() const;
            void setCellRowPosition(int position);

            int getCellColumnPosition() const;
            void setCellColumnPosition(int position);

            void openCell();
            bool canOpenCell();
            void flagCell();
        };
    }
}