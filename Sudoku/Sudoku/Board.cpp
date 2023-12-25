/**
* @file Board.cpp
* @brief Implements memebers of the Board class.
* @author Nikola Jolovic
* @date 25.12.2023
*/

#include <iostream>
#include <string>
#include <sstream>
#include "Board.hpp"
#include "../Constants.hpp"

using Constants::BOARD_SIZE;
using Constants::BLOCK_SIZE;

namespace Sudoku {
	Board::Board(): board() {}

	Board::Board(const Board& other): board() {
		for(int i=0; i<BOARD_SIZE; i++){
			for(int j=0; j<BOARD_SIZE; j++){
				this->board[i][j] = other[i][j];
			}
		}
	}

	Board& Board::operator=(const Board& other){
		for(int i=0; i<BOARD_SIZE; i++){
			for(int j=0; j<BOARD_SIZE; j++){
				this->board[i][j] = other[i][j];
			}
		}
		return *this;
	}

	char* Board::operator[](int rowIdx){
		return this->board[rowIdx];
	}

	const char* Board::operator[](int rowIdx) const {
		return this->board[rowIdx];
	}

	std::istream& operator>>(std::istream& in, Board& board){
		std::string str;
		std::getline(in, str); // first line (delimiters only)
		for(int i=0; i<BOARD_SIZE; i++){
			std::getline(in, str);
			std::stringstream ss(str);
			ss.ignore(2); // delimiter
			for(int j=0; j<BOARD_SIZE; j++){
				char ch;
				ss.get(ch);
				if(ch == ' ')
					board[i][j] = Constants::EMPTY_CELL;
				else
					board[i][j] = ch;
				ss.ignore(3); // delimiter
			}
			std::getline(in, str); // delimiter line
		}
		return in;
	}

	std::ostream& operator<<(std::ostream& out, const Board& board){
		for(int j=0; j<BOARD_SIZE; j++)
			out << " ---";
		out << " \n";
		for(int i=0; i<BOARD_SIZE; i++){
			for(int j=0; j<BOARD_SIZE; j++){
				if(board[i][j] == Constants::EMPTY_CELL)
					out << "|   ";
				else
					out << "| " << board[i][j] << ' ';
			}
			out << "|\n";
			// delimiter row
			for(int j=0; j<BOARD_SIZE; j++)
				out << " ---";
			out << " \n";
		}
		return out;
	}

	int Board::getBlockNum(int rowIdx, int colIdx) {
		return (rowIdx/BLOCK_SIZE)*BLOCK_SIZE + colIdx/BLOCK_SIZE;
	}
}