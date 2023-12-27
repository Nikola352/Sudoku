#include "pch.h"
#include "../Sudoku/Checker/SudokuChecker.hpp"
#include "../Sudoku/Checker/SudokuChecker.cpp"
#include "../Sudoku/Sudoku/Board.hpp"
#include "../Sudoku/Sudoku/Board.cpp"
#include "../Sudoku/Constants.hpp"
#include "Constants.hpp"

using Constants::BOARD_SIZE;
using namespace TestConstants;

class SudokuCheckerTest : public ::testing::Test {
protected:
	Sudoku::SudokuChecker checker;
	int correct_values, incorrect_values, empty_cells;
	Sudoku::Board empty_board;
	Sudoku::Board valid_board;

	void SetUp() override {
		correct_values = incorrect_values = empty_cells = 0;
		valid_board = Sudoku::Board(valid_matrix);
	}
};

TEST_F(SudokuCheckerTest, IsEmptyValid){
	ASSERT_TRUE(checker.isValid(empty_board));
}

TEST_F(SudokuCheckerTest, IsEmptySolved){
	ASSERT_FALSE(checker.isSolved(empty_board, empty_board, correct_values, incorrect_values, empty_cells));
}

TEST_F(SudokuCheckerTest, ValidBoard){
	ASSERT_TRUE(checker.isValid(valid_board));
}

TEST_F(SudokuCheckerTest, InvalidRow){
	Sudoku::Board board(row_invalid_matrix);
	ASSERT_FALSE(checker.isValid(board));
}

TEST_F(SudokuCheckerTest, InvalidColumn){
	Sudoku::Board board(col_invalid_matrix);
	ASSERT_FALSE(checker.isValid(board));
}

TEST_F(SudokuCheckerTest, InvalidBlock){
	Sudoku::Board board(block_invalid_matrix);
	ASSERT_FALSE(checker.isValid(board));
}

TEST_F(SudokuCheckerTest, ValidSolution){
	Sudoku::Board board(solution_matrix);
	bool good = checker.isSolved(board, valid_board, correct_values, incorrect_values, empty_cells);
	EXPECT_EQ(correct_values, 56);
	EXPECT_EQ(incorrect_values, 0);
	EXPECT_EQ(empty_cells, 0);
	ASSERT_TRUE(good);
}

TEST_F(SudokuCheckerTest, IncorrectFull){
	Sudoku::Board board(incorrect_full_matrix);
	bool good = checker.isSolved(board, valid_board, correct_values, incorrect_values, empty_cells);
	EXPECT_EQ(correct_values, 52);
	EXPECT_EQ(incorrect_values, 4);
	EXPECT_EQ(empty_cells, 0);
	ASSERT_FALSE(good);
}

TEST_F(SudokuCheckerTest, IncorrectMissing){
	Sudoku::Board board(missing_matrix);
	bool good = checker.isSolved(board, valid_board, correct_values, incorrect_values, empty_cells);
	EXPECT_EQ(correct_values, 55);
	EXPECT_EQ(incorrect_values, 0);
	EXPECT_EQ(empty_cells, 1);
	ASSERT_FALSE(good);
}

TEST_F(SudokuCheckerTest, IncorrectTempered){
	Sudoku::Board board(tempered_correct_matrix);
	bool good = checker.isSolved(board, valid_board, correct_values, incorrect_values, empty_cells);
	EXPECT_EQ(correct_values, 56);
	EXPECT_EQ(incorrect_values, 9);
	EXPECT_EQ(empty_cells, 0);
	ASSERT_FALSE(good);
}