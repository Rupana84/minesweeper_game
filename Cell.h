//
// Created by Gavy Singh on 2025-11-19.
//

#ifndef MINESWEEPER_LOGIC_GAME_CELL_H
#define MINESWEEPER_LOGIC_GAME_CELL_H
#endif //MINESWEEPER_LOGIC_GAME_CELL_H

#ifndef CELL_H
#define CELL_H

// Represents ONE square on the Minesweeper board.
// A cell stores:
// The Board class manages a 2D grid of these Cell objects.


class Cell {
private:
    bool hasMine;
    bool revealed;
    bool flagged;
    int  adjacentMines;

    //Setters
public:
    Cell();

    void setMine(bool value);
    void setAdjacentMines(int count);


    void reveal();
    void toggleFlag();


    // Getters — used by Board and Game logic

    bool isMine() const;
    bool isRevealed() const;
    bool isFlagged() const;
    int  getAdjacentMines() const;  // returns 0–8
    char displayChar(bool revealMines) const;
};

#endif // CELL_H