#include "pch.h"
#include "../Sudoku/Sudoku/Board.hpp"
#include "../Sudoku/FileIO/FileIO.hpp"
#include "../Sudoku/FileIO/FileIO.cpp"
#include "Constants.hpp"
#include <cstdio>

class FileIOTest : public ::testing::Test {
protected:
	char* path;

	void SetUp() override {
		path = "tmp_board.txt";
	}

	void TearDown() override {
		std::remove(path);
	}
};

TEST_F(FileIOTest, ValidSolve) {
	Sudoku::Board board(TestConstants::valid_matrix);
	FileIO::saveToFile(path, board);

	Sudoku::Board board2;
	FileIO::loadFromFile(path, board2);

	for(int i=0; i<BOARD_SIZE; i++){
		for(int j=0; j<BOARD_SIZE; j++){
			ASSERT_EQ(board[i][j], board2[i][j]);
		}
	}
}