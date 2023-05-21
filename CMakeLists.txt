cmake_minimum_required(VERSION 3.25)
project(game_sokoban)

set(CMAKE_CXX_STANDARD 17)

add_executable(game_sokoban solver/state.cpp solver/state.h solver/move.cpp solver/move.h solver/solver.cpp solver/solver.h)
