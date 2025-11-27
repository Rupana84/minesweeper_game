//
// Created by Gavy Singh on 2025-11-23.
//

#ifndef MINESWEEPER_LOGIC_GAME_GAME_H
#define MINESWEEPER_LOGIC_GAME_GAME_H
#endif // MINESWEEPER_LOGIC_GAME_GAME_H

// Game.h
#ifndef GAME_H
#define GAME_H

#include <memory>
#include <string>
#include "Board.h"

class Game {
private:
    std::unique_ptr<Board> board;
    bool gameOver;
    bool playerWon;
    bool quitRequested;

    void handleMove();
    bool parseCoordinate(const std::string& input, int& row, int& col) const;

public:
    Game(int rows, int cols, int mines);

    void run();   // main loop
};

#endif // GAME_H