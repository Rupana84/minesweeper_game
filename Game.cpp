//
// Created by Gavy Singh on 2025-11-25.
//

#include "Game.h"
#include "Board.h"
#include <iostream>
#include <limits>

// Creates a new Board on the heap using std::make_unique.
// Initializes game state: not over, not won yet.
Game::Game(int rows, int cols, int mines)
    : board(std::make_unique<Board>(rows, cols, mines)),
      gameOver(false),
      playerWon(false),
      quitRequested(false) {}


// Converts user input such as "b3", "C7", "a10" into numeric
// grid positions (zero-indexed).
// row  = letter part  ('a' -> 0, 'b' -> 1, etc.)
// col  = number part  ("3" -> 2)
// Returns TRUE if coordinate format is valid.
// Returns FALSE if:
//   - too short
//   - row is not a letter
//   - column is not a number
bool Game::parseCoordinate(const std::string& input, int& row, int& col) const {
    if (input.size() < 2) return false;

    // first character must be a letter
    char rChar = static_cast<char>(tolower(input[0]));
    if (rChar < 'a' || rChar > 'z') return false;

    row = rChar - 'a';

    // rest must be a number
    std::string numPart = input.substr(1);
    int c = 0;
    try {
        c = std::stoi(numPart);
    } catch (...) {
        return false;
    }

    col = c - 1;

    // VALIDATION (rows and cols must exist)
    if (row < 0 || row >= board->getRows()) return false;
    if (col < 0 || col >= board->getCols()) return false;

    return true;
}

// Reads one full player action and executes it.
// Supported actions:
// After the action, checks for:
//   - mine hit  (lose game)
//   - all safe cells revealed (win game)
// ------------------------------------------------------------
void Game::handleMove() {
    std::cout << "Välj åtgärd (o = öppna, f = flagga, q = avsluta): ";
    char action;

    if (!(std::cin >> action)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ogiltig inmatning.\n";
        return;
    }

    // quit game
    if (action == 'q' || action == 'Q') {
        gameOver = true;
        quitRequested = true;
        return;
    }

    // only allow o/f here
    if (!(action == 'o' || action == 'O' ||
          action == 'f' || action == 'F')) {
        std::cout << "Ogiltigt kommando. Använd o (öppna), f (flagga) eller q (avsluta).\n";
        return;
          }

    std::cout << "Ange ruta (t.ex. b3): ";
    std::string coord;
    std::cin >> coord;

    int row = 0, col = 0;
    if (!parseCoordinate(coord, row, col)) {
        std::cout << "Ogiltig koordinat.\n";
        return;
    }

    // if cell already open: tell user and do nothing
    if (board->isRevealed(row, col)) {
        std::cout << "Den här rutan är redan öppnad.\n";
        return;
    }

    // toggle flag
    if (action == 'f' || action == 'F') {
        board->toggleFlag(row, col);
        return;
    }

    // reveal cell
    if (action == 'o' || action == 'O') {
        bool hitMine = board->revealCell(row, col);

        if (hitMine) {
            gameOver = true;
            playerWon = false;
            return;
        }

        if (board->allSafeCellsRevealed()) {
            gameOver = true;
            playerWon = true;
        }
        return;
    }

    std::cout << "Ogiltigt kommando.\n";
}

void Game::run() {
    while (!gameOver) {
        board->print(false);  //hide mines during play
        handleMove();
    }

    if (quitRequested) {
        // Player chose to quit manually – do not reveal all mines
        board->print(false);
        std::cout << "Du avslutade spelet.\n";
        return;
    }

    // Game ended by win or by hitting a mine – show full board with mines
    board->print(true);

    if (playerWon) {
        std::cout << "Grattis! Du rensade alla säkra rutor.\n";
    } else {
        std::cout << "Game Over – du träffade en mina.\n";
    }
}