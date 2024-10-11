#pragma once
#include <random>
#include <vector>

namespace Gameplay
{
    namespace Cell
    {
        class CellController;
        enum class CellAction;
    }

    namespace Board
    {
        enum class BoardState
        {
            FIRST_CELL,       // The state when the player opens first cell.
            PLAYING,          // The game is in progress.
            COMPLETED,    // The game is over.
        };

        class BoardController
        {
        private:
            static const int default_number_of_rows = 0;
            static const int default_number_of_columns = 0;
            static const int default_mines_count = 0;

            int selected_number_of_rows = default_number_of_rows;
            int selected_number_of_columns = default_number_of_columns;
            int selected_mines_count = default_mines_count;

            int number_of_rows;
            int number_of_columns;
            int mines_count;

            // Use a vector of vectors for the 2D array
            std::vector<std::vector<Cell::CellController*>> board;
            BoardState board_state;

            int flagged_cells;

            // To generate random values.
            std::default_random_engine random_engine;

            // To give random seed to generator.
            std::random_device random_device;

            void createBoard();

            void populateMines(int row, int column);
            void populateCells();
            void populateBoard(int row, int column);
            void processCellValue(int row, int column);
            void processMineCell(int row, int column);
            void processEmptyCell(int row, int column);
            bool isValidCellPosition(int row, int column) const;
            bool areAllCellOpen();
            int countMinesAround(int row, int column) const;

            void resizeVector();

            void destroy();
            void resetBoard();
            void deleteBoard();

        public:
            BoardController();
            ~BoardController();

            void initialize();
            void update();
            void render();
            void reset();

            void openAllCells();
            void openEmptyCells(int row, int column);
            void openCell(int row, int column);
            void flagAllMines();
            void flagCell(int row, int column);
            void processCellInput(int row, int column, Cell::CellAction action);
            void displayGrid();

            void showBoard();

            int getSelectedRowsCount() const;
            void setSelectedRowsCount(int count);
            int getSelectedColumnsCount() const;
            void setSelectedColumnsCount(int count);
            int getSelectedMinesCount() const;
            void setSelectedMinesCount(int count);

            int getRowsCount() const;
            int getColumnsCount() const;
            int getMinesCount() const;

            BoardState getBoardState() const;
            void setBoardState(BoardState state);
        };
    }
}