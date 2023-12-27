/**
* @file SudokuChecker.cpp
* @brief Implements the SudokuChecker.
* @author Nikola Jolovic
* @date 26.12.2023.
*/

#include <bitset>
#include <vector>
#include "SudokuChecker.hpp"
#include "../Constants.hpp"
#include "../Solver/SudokuSolver.hpp"

using Constants::BOARD_SIZE;
using Constants::BLOCK_SIZE;

namespace Sudoku{
	bool SudokuChecker::isValid(const Board& board) {
		// distinct values in every row
		for(int i=0; i<BOARD_SIZE; i++){
			this->valueSet.reset();
			for(int j=0; j<BOARD_SIZE; j++){
				if(board[i][j] == Constants::EMPTY_CELL)
					continue;
				int idx = Constants::KEY_IDX.at(board[i][j]);
				if(this->valueSet.test(idx))
					return false;
				this->valueSet[idx] = true;
			}
		}

		// distinct values in every column
		for(int j=0; j<BOARD_SIZE; j++){
			this->valueSet.reset();
			for(int i=0; i<BOARD_SIZE; i++){
				if(board[i][j] == Constants::EMPTY_CELL)
					continue;
				int idx = Constants::KEY_IDX.at(board[i][j]);
				if(this->valueSet.test(idx))
					return false;
				this->valueSet[idx] = true;
			}
		}

		// distinct values in every block
		for(int k=0; k<BOARD_SIZE; k++){
			this->valueSet.reset();
			for(int i=0; i<BLOCK_SIZE; i++){
				for(int j=0; j<BLOCK_SIZE; j++){
					int ri = (k/BLOCK_SIZE)*BLOCK_SIZE + i;
					int ci = (k%BLOCK_SIZE)*BLOCK_SIZE + j;
					if(board[ri][ci] == Constants::EMPTY_CELL)
						continue;
					int idx = Constants::KEY_IDX.at(board[ri][ci]);
					if(this->valueSet.test(idx))
						return false;
					this->valueSet[idx] = true;
				}
			}
		}

		return true;
	}

	bool SudokuChecker::isSolved(const Board& board, const Board& start_board,
		int& correct_values, int& incorrect_values, int& empty_cells
	) const {
		std::vector<std::vector<int>> rows(BOARD_SIZE, std::vector<int>(BOARD_SIZE, 0)); // rows[i][j] = count of j-th character in i-th row
		std::vector<std::vector<int>> cols(BOARD_SIZE, std::vector<int>(BOARD_SIZE, 0));
		std::vector<std::vector<int>> blocks(BOARD_SIZE, std::vector<int>(BOARD_SIZE, 0));

		for(int i=0; i<BOARD_SIZE; i++){
			for(int j=0; j<BOARD_SIZE; j++){
				if(board[i][j] == Constants::EMPTY_CELL)
					continue;
				int idx = Constants::KEY_IDX.at(board[i][j]);
				rows[i][idx]++;
				cols[j][idx]++;
				blocks[Sudoku::Board::getBlockNum(i, j)][idx]++;
			}
		}

		bool is_tempered_with = false; // indicates wether the numbers from the initial board were changed.
		correct_values = incorrect_values = empty_cells = 0;
		for(int i=0; i<BOARD_SIZE; i++){
			for(int j=0; j<BOARD_SIZE; j++){
				if(board[i][j] == Constants::EMPTY_CELL){
					empty_cells++;
					if(start_board[i][j] != Constants::EMPTY_CELL){
						is_tempered_with = true;
					}
					continue;
				}
				int idx = Constants::KEY_IDX.at(board[i][j]);
				if(start_board[i][j] != Constants::EMPTY_CELL){
					if(board[i][j] != start_board[i][j]){
						is_tempered_with = true;
						incorrect_values++;
					}
					continue;
				}
				if(rows[i][idx] > 1)
					incorrect_values++;
				else if(cols[j][idx] > 1)
					incorrect_values++;
				else if(blocks[Sudoku::Board::getBlockNum(i, j)][idx] > 1)
					incorrect_values++;
				else
					correct_values++;
			}
		}

		return (!is_tempered_with && incorrect_values == 0 && empty_cells == 0);
	}
}