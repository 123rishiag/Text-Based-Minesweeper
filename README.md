# Text Based Minesweeper

## Overview
Welcome to **Text Based Minesweeper**, a console-based version of the classic puzzle game where strategy and logic are your best friends in avoiding hidden mines. This project is written in C++ and uses a text-based interface, offering a minimalist take on the iconic Minesweeper game.

## Features
- **Grid Mechanics**: 
  - Navigate through a grid of cells and uncover safe areas while avoiding hidden mines.
  - Use adjacent cell clues to determine the location of mines.
- **Mine Detection**: 
  - Open cells to reveal their contents and gather information on nearby mines.
  - Flag cells where you suspect a mine might be hidden.
- **Game State Management**: 
  - Smooth transitions between win/loss conditions.
  - Checks for game over scenarios with every move.
- **Text-Based UI**: 
  - Simple text symbols to represent each cell’s state for clear, concise gameplay.

## Learning Outcomes

- **Data Structures**: Gained experience in using 2D arrays to manage a grid-based system.
- **Game Logic**: Enhanced understanding of state management and implementing core game mechanics for win/lose conditions.
- **User Interaction**: Designed an interactive text-based interface that smoothly handles user input.
- **Object-Oriented Design**: Refined OOP skills by structuring the game with services, controllers, and models.
- **Game Loop and State Management**: Implemented a consistent and reliable game loop to manage real-time gameplay.

## Project Structure

### Services and Their Model, Controllers

- **GameplayService**: Manages core gameplay mechanics, including checking win/lose conditions and processing player inputs.
  - Includes: `GameplayController`
  
- **BoardService**: Manages the grid layout and interactions between cells.
  - Includes: `BoardController`, `CellController`, `CellModel`

### Additional Core Components

- **Main**: The entry point for the game, defined in `main.cpp`.
  
- **GameService**: The core service managing game initialization, updating, and state transitions.
  
- **ServiceLocator**: Coordinates the initialization, updating, and rendering of all services.

## How to Play

### Rules:
1. The board is divided into cells, with mines randomly distributed across the grid.
2. Your objective is to open all safe cells without triggering a mine.
3. The number on a cell indicates the number of mines adjacent to it.
4. Flag a cell if you suspect it contains a mine. Flagged cells cannot be opened until unflagged.
5. Interact, evolve, and enjoy the game!

### Controls:
- Enter the coordinates of the cell you want to open (space separated).
  Example: `5 10`
- To flag a cell, input the coordinates followed by 'F'.
  Example: `5 10 F`

### Symbols:
- `'+'` - Unopened Cell  
- `'F'` - Flagged Cell  
- `'*'` - Mine Cell  
- `' '` - Blank Cell (Safe area)

### Instructions:
1. Input the grid size (`n*n`) where `n` must be between `9` and `15`.
2. Enter coordinates to open cells or flag them.
3. Continue until all safe cells are opened or a mine is triggered.
4. After each move, the game checks if you've won or lost.

## How to Build and Run

1. **Clone the repository**:
   ```bash
   git clone https://github.com/123rishiag/Text-Based-Minesweeper.git
   ```

2. **Build the project** using a C++ compiler.
   - Make sure the necessary dependencies for the console environment are met.

3. **Run the executable** to start the game.

## Video Demo
Watch the [Video Demo](https://www.loom.com/share/43b98f0a48e34db3b6a647b878c6d77e?sid=dba471ed-1d36-4de1-84f8-2c6a21ffddb0) to understand Minesweeper's gameplay!