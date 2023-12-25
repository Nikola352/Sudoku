#pragma once

#include <string>
#include "../Sudoku/Board.hpp"

namespace FileIO{
	void loadFromFile(std::string filename, Sudoku::Board& board);
	void saveToFile(std::string filename, const Sudoku::Board& board);
}