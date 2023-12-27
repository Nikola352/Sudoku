#include "pch.h"
#include "../Sudoku/Generator/SudokuGenerator.hpp"
#include "../Sudoku/Generator/SudokuGenerator.cpp"
#include "../Sudoku/Solver/SudokuSolver.hpp"
#include "../Sudoku/Checker/SudokuChecker.hpp"
#include "../Sudoku/Sudoku/Board.hpp"
#include "../Sudoku/Sudoku/MarkedBoard.hpp"
#include "../Sudoku/Constants.hpp"

using Constants::BOARD_SIZE;

class SudokuGeneratorTest : public ::testing::Test {
protected:
	Sudoku::SudokuGenerator generator;
	Sudoku::MarkedBoard board;
	Sudoku::SudokuChecker checker;
	Sudoku::SudokuSolver solver;
	
	SudokuGeneratorTest() : generator(Sudoku::MEDIUM, false), board() {}

	void checkBoard(Sudoku::Board& board){
		ASSERT_TRUE(checker.isValid(board));
		Sudoku::MarkedBoard solved(board);
		ASSERT_TRUE(solver.solve(board, solved));
	}

	int countEmpty(const Sudoku::Board& board){
		int empty_cnt = 0;
		for(int i=0; i<BOARD_SIZE; i++){
			for(int j=0; j<BOARD_SIZE; j++){
				if(board[i][j] == Constants::EMPTY_CELL)
					empty_cnt++;
			}
		}
		return empty_cnt;
	}
};

TEST_F(SudokuGeneratorTest, GenerateDefault) {
	generator.generateBoard(board);
	checkBoard(board);
}

TEST_F(SudokuGeneratorTest, Easy){
	generator.setDifficulty(Sudoku::EASY);
	generator.generateBoard(board);
	checkBoard(board);
	int empty_cnt = countEmpty(board);
	ASSERT_GE(empty_cnt, 10);
	ASSERT_LE(empty_cnt, 30);
}

TEST_F(SudokuGeneratorTest, Medium){
	generator.setDifficulty(Sudoku::MEDIUM);
	generator.generateBoard(board);
	checkBoard(board);
	int empty_cnt = countEmpty(board);
	ASSERT_GE(empty_cnt, 31);
	ASSERT_LE(empty_cnt, 50);
}

TEST_F(SudokuGeneratorTest, Hard){
	generator.setDifficulty(Sudoku::HARD);
	generator.generateBoard(board);
	checkBoard(board);
	int empty_cnt = countEmpty(board);
	ASSERT_GE(empty_cnt, 51);
	ASSERT_LE(empty_cnt, 64);
}

TEST_F(SudokuGeneratorTest, Unique){
	generator.setUnique(true);
	generator.generateBoard(board);
	checkBoard(board);
}