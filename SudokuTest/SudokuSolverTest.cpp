#include "pch.h"
#include "../Sudoku/Solver/SudokuSolver.hpp"
#include "../Sudoku/Solver/SudokuSolver.cpp"
#include "../Sudoku/Checker/SudokuChecker.hpp"
#include "../Sudoku/Sudoku/Board.hpp"
#include "../Sudoku/Sudoku/MarkedBoard.hpp"
#include "../Sudoku/Sudoku/MarkedBoard.cpp"
#include "Constants.hpp"

class SudokuSolverTest : public ::testing::Test {
protected:
	Sudoku::SudokuSolver solver;
	Sudoku::SudokuChecker checker;
	int correct_values, incorrect_values, empty_cells;
};

TEST_F(SudokuSolverTest, ValidSolve) {
	Sudoku::Board start_board(TestConstants::valid_matrix);
	Sudoku::MarkedBoard board;
	ASSERT_TRUE(solver.solve(start_board, board));
	ASSERT_TRUE(checker.isSolved(board, start_board, correct_values, incorrect_values, empty_cells));
}

TEST_F(SudokuSolverTest, Impossible) {
	Sudoku::Board start_board(TestConstants::impossible_matrix);
	Sudoku::MarkedBoard board;
	ASSERT_FALSE(solver.solve(start_board, board));
	for(int i=0; i<BOARD_SIZE; i++){
		for(int j=0; j<BOARD_SIZE; j++){
			ASSERT_EQ(board[i][j], start_board[i][j]);
		}
	}
}