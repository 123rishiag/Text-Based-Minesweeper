#pragma once

namespace Gameplay
{
    namespace Cell
    {
        enum class CellAction;
    }

    namespace Board
    {
        class BoardController;
        enum class BoardState;

        class BoardService
        {
        private:
            Board::BoardController* board_controller;

            void destroy();

        public:
            BoardService();
            ~BoardService();

            void initialize();
            void update();
            void render();

            void flagAllMines();

            void processCellInput(int row, int column, Cell::CellAction action);
            void displayGrid();

            void showBoard();
            void resetBoard();
            void resetBoard(int rows, int columns, int mines);

            int getSelectedRowsCount() const;
            int getSelectedColumnsCount() const;
            int getSelectedMinesCount() const;

            int getMinesCount() const;
            BoardState getBoardState() const;
            void setBoardState(BoardState state);
        };
    }
}