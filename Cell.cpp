//
// Created by Gavy Singh on 2025-11-19.
//

#include "Cell.h"
Cell::Cell()
    : hasMine(false), revealed(false), flagged(false), adjacentMines(0) {}

// setMine()
// Used by Board::placeMines() to mark this cell as containing a mine.

void Cell::setMine(bool value) {
    hasMine = value;
}

// setAdjacentMines()
// Used by Board::computeAdjacency() to store number of nearby mines.

void Cell::setAdjacentMines(int count) {
    adjacentMines = count;
}

// reveal()
// Marks the cell as revealed.
// Called when the player chooses a cell to open.
void Cell::reveal() {
    revealed = true;
}

// toggleFlag()
// Flags/unflags this cell *only if it is still hidden*.
// Prevents players from flagging already revealed cells.

void Cell::toggleFlag() {
    if (!revealed) {
        flagged = !flagged;   // flip the state (true->false, false->true)
    }
}

// Getter: isMine()
// Returns true if this cell contains a mine.

bool Cell::isMine() const {
    return hasMine;
}

// Getter: isRevealed()
// Returns true if player has revealed this cell.

bool Cell::isRevealed() const {
    return revealed;
}

// Getter: isFlagged()
// Returns true if player flagged this cell as a suspected mine.

bool Cell::isFlagged() const {
    return flagged;
}

// Getter: getAdjacentMines()
// Returns how many mines are next to this cell (0–8).

int Cell::getAdjacentMines() const {
    return adjacentMines;
}


char Cell::displayChar(bool revealMines) const {
    // Case 1: Cell has been revealed
    if (revealed) {
        if (hasMine) return '*';
        if (adjacentMines == 0) return ' ';
        return '0' + adjacentMines;
    }

    // Case 2: Hidden but flagged by player
    if (flagged) return 'F';

    // Case 3: Hidden but we want to show mines (only after losing)
    if (revealMines && hasMine) return '*';

    // Case 4: Hidden normal cell
    return '#';
}