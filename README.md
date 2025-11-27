Minesweeper – Text-Based C++ Game

A simple console implementation of the classic Minesweeper game, written in modern C++ using classes (Cell, Board, Game).
The project demonstrates object-oriented programming, input validation, adjacency calculations, and structured game logic.

⸻

   Features
	•	2D board with configurable rows, columns, and number of mines
	•	Reveal or flag cells
	•	Random mine placement using the <random> library
	•	Correct adjacency number calculation (0–8)
	•	Win detection: all safe cells must be revealed
	•	Loss detection: revealing a mine ends the game
	•	Clean code structured into separate classes

⸻

   How the Game Works
	•	Use:
	•	o → open a cell
	•	f → flag or unflag a cell
	•	q → quit the game
	•	Coordinates must be written like:
	•	a3, c7, h1, etc.
	•	Letter = row, number = column
	•	If you open a cell containing a mine → Game Over
	•	If you reveal all NON-mine cells → You win

⸻

   Project Structure
   Minesweeper_Logic_Game/
│
├── Cell.h / Cell.cpp        → Represents a single cell (mine, flag, revealed, number)
├── Board.h / Board.cpp      → Owns the 2D grid, places mines, calculates adjacency
├── Game.h / Game.cpp        → Main game loop, user input, win/lose logic
└── main.cpp                 → Creates a Game object and starts the game

 Class Overview

Cell
	•	Stores:
	•	hasMine
	•	revealed
	•	flagged
	•	adjacentMines
	•	Manages reveal/flag actions
	•	Displays correct character (#, F, 1–8, *)

⸻

Board
	•	Creates a 2D grid of Cell objects
	•	Places mines randomly
	•	Counts adjacent mines for each cell
	•	Handles reveal/flag logic
	•	Detects win condition
	•	Renders the board

⸻

Game
	•	Controls the game loop
	•	Reads and validates user commands
	•	Interprets coordinates
	•	Ends the game on win/lose/quit

⸻

 How to Compile & Run

Using g++
g++ -std=c++17 main.cpp Game.cpp Board.cpp Cell.cpp -o minesweeper
./minesweeper

CLion / VSCode
	•	CMakeLists is already configured
	•	Build → Run

Example Output

   1 2 3 4 5 6 7 8 9
  +------------------+
a |# # # # # # # # # |
b |# # # # # # # # # |
...
Välj åtgärd (o = öppna, f = flagga, q = avsluta):

 Learning Goals Demonstrated
	•	Use of classes and object-oriented design
	•	Use of std::vector, std::unique_ptr, and 
	•	Clean separation of logic across multiple files
	•	Input validation and safe checks (inBounds)
	•	Console rendering

⸻

 Requirements Coverage (G Level)

 Text-based Minesweeper
 Random mines
 Reveal & flag actions
 Win detection
 Loss detection
 Input validation
 Clean code & class structure
 No recursion requirement removed if disabled
