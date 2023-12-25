/**
* @file SudokuSolver.cpp
* @brief Implements the SudokuSolver.
* @author Nikola Jolovic
* @date 25.12.2023
*/

#include <bitset>
#include "SudokuSolver.hpp"
#include "../Sudoku/Board.hpp"
#include "../Sudoku/MarkedBoard.hpp"
#include "../Constants.hpp"

using Constants::BOARD_SIZE;

namespace Solver{
	void SudokuSolver::solve(const Sudoku::Board& start_board, Sudoku::MarkedBoard& solution_board) const {
		solution_board = start_board;
		this->solve(solution_board, 0, 0);
	}

	bool SudokuSolver::solve(Sudoku::MarkedBoard& board, int ri, int ci) const {
		while(ri < 9 && board[ri][ci] != Constants::EMPTY_CELL){
			if(++ci == 9){
				ci = 0;
				ri++;
			}
		}
		if(ri == 9) return true;
		std::bitset<BOARD_SIZE> taken = 
			board.rowSets[ri] | board.colSets[ci] | board.blockSets[Sudoku::Board::getBlockNum(ri, ci)];
		for(int k=0; k<BOARD_SIZE; k++){
			if(taken.test(k))
				continue;
			board[ri][ci] = Constants::ALPHABET[k];
			board.rowSets[ri][k] = board.colSets[ci][k] = board.blockSets[Sudoku::Board::getBlockNum(ri, ci)][k] = true;
			if(this->solve(board, ri, ci))
				return true;
			board[ri][ci] = Constants::EMPTY_CELL;
			board.rowSets[ri][k] = board.colSets[ci][k] = board.blockSets[Sudoku::Board::getBlockNum(ri, ci)][k] = false;
		}
		return false;
	}
}