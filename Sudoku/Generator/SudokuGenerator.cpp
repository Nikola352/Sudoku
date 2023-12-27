/**
* @file SudokuGenerator.cpp
* @brief Implements the SudokuGenerator.
* @author Nikola Jolovic
* @date 26.12.2023
*/

#include <bitset>
#include <vector>
#include <algorithm>
#include <ctime>
#include <stack>
#include <utility>
#include "SudokuGenerator.hpp"
#include "../Sudoku/Board.hpp"
#include "../Sudoku/MarkedBoard.hpp"
#include "../Constants.hpp"

namespace Sudoku{
	SudokuGenerator::SudokuGenerator() : difficulty(MEDIUM), unique(false), random_gen(time(0)) {}

	SudokuGenerator::SudokuGenerator(Difficulty difficulty=MEDIUM, bool unique=false)
		: difficulty(difficulty), unique(unique), random_gen(time(0)) {}

	void SudokuGenerator::setDifficulty(Difficulty difficulty){
		this->difficulty = difficulty;
	}

	void SudokuGenerator::setUnique(bool unique){
		this->unique = unique;
	}

	void SudokuGenerator::fillBoard(Board& board){
		MarkedBoard marked_board = board;
		this->fillBoardFrom(marked_board, 0, 0);
		board = marked_board;
	}

	bool SudokuGenerator::fillBoardFrom(MarkedBoard& board, int ri, int ci){
		while(ri < 9 && board[ri][ci] != Constants::EMPTY_CELL){
			if(++ci == 9){
				ci = 0;
				ri++;
			}
		}
		if(ri == 9) return true;
		std::bitset<BOARD_SIZE> taken =
			board.rowSets[ri] | board.colSets[ci] | board.blockSets[Board::getBlockNum(ri, ci)];
		std::vector<int> possible;
		for(int k=0; k<BOARD_SIZE; k++){
			if(!taken.test(k))
				possible.push_back(k);
		}
		std::shuffle(possible.begin(), possible.end(), this->random_gen);
		for(int k : possible){
			board[ri][ci] = Constants::ALPHABET[k];
			board.rowSets[ri][k] = board.colSets[ci][k] = board.blockSets[Board::getBlockNum(ri, ci)][k] = true;
			if(this->fillBoardFrom(board, ri, ci))
				return true;
			board[ri][ci] = Constants::EMPTY_CELL;
			board.rowSets[ri][k] = board.colSets[ci][k] = board.blockSets[Board::getBlockNum(ri, ci)][k] = false;
		}
		return false;
	}

	int SudokuGenerator::randomIndex(){
		return this->random_gen() % Constants::BOARD_SIZE;
	}

	void SudokuGenerator::generateBoard(Board& board){
		this->fillBoard(board);
		if(this->unique){
			this->generateUnique(board);
		} else {
			this->generate(board);
		}
	}

	void SudokuGenerator::generate(Board& board){
		int cells_to_clear = 0;
		if(this->difficulty == EASY){
			std::uniform_int_distribution<int> dist(10, 30);
			cells_to_clear = dist(this->random_gen);
		} else if(this->difficulty == MEDIUM){
			std::uniform_int_distribution<int> dist(31, 50);
			cells_to_clear = dist(this->random_gen);
		} else {
			std::uniform_int_distribution<int> dist(51, 64);
			cells_to_clear = dist(this->random_gen);
		}
		for(int _=0; _<cells_to_clear; _++){
			int row, col;
			do{
				row = random_gen() % Constants::BOARD_SIZE;
				col = random_gen() % Constants::BOARD_SIZE;
			} while(board[row][col] == Constants::EMPTY_CELL);
			board[row][col] = Constants::EMPTY_CELL;
		}
	}

	int SudokuGenerator::solutionCount(MarkedBoard& board, int ri=0, int ci=0){
		while(ri < 9 && board[ri][ci] != Constants::EMPTY_CELL){
			if(++ci == 9){
				ci = 0;
				ri++;
			}
		}
		if(ri == 9) return 1;
		int solution_cnt = 0;
		std::bitset<BOARD_SIZE> taken =
			board.rowSets[ri] | board.colSets[ci] | board.blockSets[Board::getBlockNum(ri, ci)];
		for(int k=0; k<BOARD_SIZE; k++){
			if(taken.test(k))
				continue;
			board[ri][ci] = Constants::ALPHABET[k];
			board.rowSets[ri][k] = board.colSets[ci][k] = board.blockSets[Board::getBlockNum(ri, ci)][k] = true;
			solution_cnt += this->solutionCount(board, ri, ci);

			// IMPORTANT: This line ensures that at most 2 solutions are ever calculated.
			if(solution_cnt > 1) break;
			
			board[ri][ci] = Constants::EMPTY_CELL;
			board.rowSets[ri][k] = board.colSets[ci][k] = board.blockSets[Board::getBlockNum(ri, ci)][k] = false;
		}
		return solution_cnt;
	}

	void SudokuGenerator::generateUnique(Board& board){
		MarkedBoard marked_board = board;
		std::stack<std::pair<int, int>> removals;
		for(int _=0; _<64; _++){ // 9x9 boards with less than 17 values are guaranteed to have multiple solutions
			int row, col;
			do{
				row = random_gen() % Constants::BOARD_SIZE;
				col = random_gen() % Constants::BOARD_SIZE;
			} while(marked_board[row][col] == Constants::EMPTY_CELL);

			char value = marked_board[row][col];
			int idx = Constants::KEY_IDX.at(value);
			
			marked_board[row][col] = Constants::EMPTY_CELL;
			marked_board.rowSets[row][idx] = marked_board.colSets[col][idx] = marked_board.blockSets[MarkedBoard::getBlockNum(row, col)][idx] = false;
			removals.push(std::make_pair(row, col));
			
			if(removals.size() < 45) // Impossible to have multiple solutions on a 9x9 board.
				continue;
			
			int sol_cnt = this->solutionCount(marked_board);
			if(sol_cnt > 1){
				marked_board[row][col] = value;
				marked_board.rowSets[row][idx] = marked_board.colSets[col][idx] = marked_board.blockSets[MarkedBoard::getBlockNum(row, col)][idx] = true;
				removals.pop();
			} else if(sol_cnt < 1){
				marked_board[row][col] = value;
				marked_board.rowSets[row][idx] = marked_board.colSets[col][idx] = marked_board.blockSets[MarkedBoard::getBlockNum(row, col)][idx] = true;
				removals.pop();
				break;
			}
		}
		size_t undo_cnt = 0;
		if(this->difficulty == EASY){
			undo_cnt = removals.size() / 2;
		} else if(this->difficulty == MEDIUM){
			undo_cnt = removals.size() / 4;
		}
		while(undo_cnt--){
			removals.pop();
		}
		while(!removals.empty()){
			std::pair<int, int> p = removals.top();
			removals.pop();
			int row = p.first, col = p.second;
			board[row][col] = Constants::EMPTY_CELL;
		}
	}
}