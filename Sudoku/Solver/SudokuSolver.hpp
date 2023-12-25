/**
* @file SudokuSolver.hpp
* @brief Defines the SudokuSolver class.
* @author Nikola Jolovic
* @date 25.12.2023
*/

#pragma once

#include "../Sudoku/Board.hpp"

namespace Solver {
    /**
     * @brief Sudoku solver class that solves a given Sudoku puzzle.
     */
    class SudokuSolver {
    public:
        /**
         * @brief Solves the Sudoku puzzle starting from the given board and updates the solution_board.
         * @param start_board The initial Sudoku board.
         * @param solution_board The Sudoku board to store the solution.
         */
        void solve(const Sudoku::Board& start_board, Sudoku::MarkedBoard& solution_board) const;

    private:
        /**
         * @brief Recursively solves the Sudoku puzzle using backtracking.
         * @param board The current state of the Sudoku board.
         * @param rowIdx The current row index being processed.
         * @param colIdx The current column index being processed.
         * @return True if the puzzle is successfully solved, false otherwise.
         */
        bool solve(Sudoku::MarkedBoard& board, int rowIdx, int colIdx) const;
    };
}
