
// Board.h
// Represents the Minesweeper board and all game logic related to cells,
// mines, revealing, flagging, and adjacency calculations.

#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <cstddef>
#include "Cell.h"


// This class contains ALL the game logic that is not directly user input.

class Board {
private:
    int rows;
    int cols;
    int mineCount;
    std::vector<std::vector<Cell>> grid;

    bool inBounds(int r, int c) const;
    void placeMines();
    void computeAdjacency();
    void floodReveal(int r, int c);

public:
    Board(int rows, int cols, int mines);

    int getRows() const;
    int getCols() const;

    // actions
    bool revealCell(int r, int c);       // returns true if mine hit
    void toggleFlag(int r, int c);

    // queries
    bool allSafeCellsRevealed() const;
    bool isRevealed(int r, int c) const;

    // rendering
    void print(bool revealMines) const;
};
#endif // BOARD_H