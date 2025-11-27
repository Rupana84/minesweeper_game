    //
    // Created by Gavy Singh on 2025-11-20.
    //

    #include "Board.h"
    #include <iostream>
    #include <random>
    #include <ctime>


    // Constructor: creates the board, fills it with empty cells,
    // then places mines randomly and calculates adjacency numbers.

    Board::Board(int rows, int cols, int mines)
        : rows(rows), cols(cols), mineCount(mines),
          grid(rows, std::vector<Cell>(cols))   // create a 2D grid of Cell objects
    {
        placeMines();         // randomly scatter mines
        computeAdjacency();   // calculate number of nearby mines for each cell
    }

    int Board::getRows() const { return rows; }
    int Board::getCols() const { return cols; }


    // Helper: checks if a coordinate is inside the board boundaries.
    // Prevents out-of-range indexing.

    bool Board::inBounds(int r, int c) const {
        return r >= 0 && r < rows && c >= 0 && c < cols;
    }


    // Randomly place mines on the board.
    // Uses C++ <random> for uniform distribution.
    // Ensures no cell receives more than one mine.

    void Board::placeMines() {
        // Random generator seeded with current time
        std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
        std::uniform_int_distribution<int> rowDist(0, rows - 1);
        std::uniform_int_distribution<int> colDist(0, cols - 1);

        int placed = 0;
        while (placed < mineCount) {
            int r = rowDist(rng);
            int c = colDist(rng);

            // Only place mine if cell is empty
            if (!grid[r][c].isMine()) {
                grid[r][c].setMine(true);
                placed++;
            }
        }
    }

    // For each non-mine cell, count how many mines exist in the
    // 8 surrounding neighbors. Store that number in the Cell.

    void Board::computeAdjacency() {
        // Neighbor coordinate offsets (8 directions)
        const int dr[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
        const int dc[8] = {-1, 0, 1,-1, 1,-1, 0, 1};

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {

                // Mines have no adjacency number (for display only)
                if (grid[r][c].isMine()) {
                    grid[r][c].setAdjacentMines(0);
                    continue;
                }

                int count = 0;

                // Check the 8 neighbors
                for (int k = 0; k < 8; ++k) {
                    int nr = r + dr[k];
                    int nc = c + dc[k];

                    if (inBounds(nr, nc) && grid[nr][nc].isMine()) {
                        count++;
                    }
                }

                grid[r][c].setAdjacentMines(count);
            }
        }
    }

    // Reveal all empty neighboring cells recursively.
    // This is the classic "flood fill" used in Minesweeper.
    // Only expands when a cell has 0 adjacent mines.

    void Board::floodReveal(int r, int c) {
        if (!inBounds(r, c)) return;

        Cell& cell = grid[r][c];

        // Stop if already revealed or flagged
        if (cell.isRevealed() || cell.isFlagged()) return;

        cell.reveal();

        // Stop flood at numbers or mines
        if (cell.getAdjacentMines() != 0 || cell.isMine()) {
            return;
        }

        // Recursively reveal all neighbors
        //for (int dr = -1; dr <= 1; ++dr) {
          //  for (int dc = -1; dc <= 1; ++dc) {
            //    if (dr == 0 && dc == 0) continue; // skip itself
              //  floodReveal(r + dr, c + dc);
         //   }
       // }
    }

    // Player attempts to reveal a cell.
    // Return true if a mine was hit (game over).

    bool Board::revealCell(int r, int c) {
        if (!inBounds(r, c)) return false;

        Cell& cell = grid[r][c];

        // Can't reveal flagged or already-revealed cells
        if (cell.isFlagged() || cell.isRevealed()) return false;

        // Reveal this cell
        cell.reveal();

        // If it's a mine → game over
        if (cell.isMine()) {
            return true;
        }

        // If empty (0 adjacent mines) → auto-reveal neighbors( disabled the version)
       // if (cell.getAdjacentMines() == 0) {
         //   floodReveal(r, c);
      //  }

        return false; // safe reveal
    }

    // Mark or unmark a cell as a suspected mine.
    // Flags do NOT reveal the cell.

    void Board::toggleFlag(int r, int c) {
        if (!inBounds(r, c)) return;
        grid[r][c].toggleFlag();
    }


    // Check if all non-mine cells have been revealed.
    // If true → player has won the game.

    bool Board::allSafeCellsRevealed() const {
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                const Cell& cell = grid[r][c];

                // If it's NOT a mine and still hidden → game not won
                if (!cell.isMine() && !cell.isRevealed()) {
                    return false;
                }
            }
        }
        return true;
    }

    bool Board::isRevealed(int r, int c) const {
        if (!inBounds(r, c)) {
            return false;
        }
        return grid[r][c].isRevealed();
    }

    // Print the board in a readable text-based format.
    // revealMines == true → show all mines (e.g. after losing)
    // revealMines == false → show only discovered info

    void Board::print(bool revealMines) const {
        // Print column numbers
        std::cout << "   ";
        for (int c = 0; c < cols; ++c) {
            std::cout << (c + 1) << ' ';
        }
        std::cout << "\n";

        // Top border
        std::cout << "  +";
        for (int c = 0; c < cols; ++c) std::cout << "--";
        std::cout << "+\n";

        // Each row
        for (int r = 0; r < rows; ++r) {
            char rowLabel = 'a' + r; // row letters: a, b, c...
            std::cout << rowLabel << " |";

            for (int c = 0; c < cols; ++c) {
                char ch = grid[r][c].displayChar(revealMines);
                std::cout << ch << ' ';
            }

            std::cout << "|\n";
        }

        // Bottom border
        std::cout << "  +";
        for (int c = 0; c < cols; ++c) std::cout << "--";
        std::cout << "+\n";
    }