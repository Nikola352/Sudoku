/**
* @file MarkedBoard.cpp
* @brief Implements memebers of the MarkedBoard class.
* @author Nikola Jolovic
* @date 25.12.2023
*/

#include "MarkedBoard.hpp"
#include "Board.hpp"

namespace Sudoku{
	MarkedBoard::MarkedBoard(){}

	MarkedBoard::MarkedBoard(const MarkedBoard& other) : Board(other) {
		for(int i=0; i<BOARD_SIZE; i++){
			this->rowSets[i] = other.rowSets[i];
			this->colSets[i] = other.colSets[i];
			this->blockSets[i] = other.blockSets[i];
		}
	}

	MarkedBoard::MarkedBoard(const Board& other) : Board(other) {
		this->calculateMarks();
	}

	MarkedBoard& MarkedBoard::operator=(const MarkedBoard& other){
		for(int i=0; i<BOARD_SIZE; i++){
			for(int j=0; j<BOARD_SIZE; j++){
				(*this)[i][j] = other[i][j];
			}
		}
		for(int i=0; i<BOARD_SIZE; i++){
			this->rowSets[i] = other.rowSets[i];
			this->colSets[i] = other.colSets[i];
			this->blockSets[i] = other.blockSets[i];
		}
		return *this;
	}

	MarkedBoard& MarkedBoard::operator=(const Board & other)
	{
		for(int i=0; i<BOARD_SIZE; i++){
			for(int j=0; j<BOARD_SIZE; j++){
				(*this)[i][j] = other[i][j];
			}
		}
		this->calculateMarks();
		return *this;
	}

	void MarkedBoard::calculateMarks() {
		for(int i=0; i<BOARD_SIZE; i++){
			this->rowSets[i].reset();
			this->colSets[i].reset();
			this->blockSets[i].reset();
		}
		for(int i=0; i<BOARD_SIZE; i++){
			for(int j=0; j<BOARD_SIZE; j++){
				if((*this)[i][j] == Constants::EMPTY_CELL)
					continue;
				int idx = Constants::KEY_IDX.at((*this)[i][j]);
				this->rowSets[i][idx] = true;
				this->colSets[j][idx] = true;
				this->blockSets[this->getBlockNum(i, j)][idx] = true;
			}
		}
	}

}