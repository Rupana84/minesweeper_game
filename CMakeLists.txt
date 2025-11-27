cmake_minimum_required(VERSION 3.16)
project(Minesweeper CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
        minesweeper
        main.cpp
        Cell.cpp
        Board.cpp
        Game.cpp
)