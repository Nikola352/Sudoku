#include <string>
#include <fstream>
#include "../Sudoku/Board.hpp"
#include "FileIO.hpp"

namespace FileIO{
	void loadFromFile(std::string filename, Sudoku::Board& board){
		std::ifstream in(filename);
		in >> board;
	}
	
	void saveToFile(std::string filename, const Sudoku::Board& board){
		std::ofstream out(filename);
		out << board;
	}
}