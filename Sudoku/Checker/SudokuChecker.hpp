/**
* @file SudokuChecker.hpp
* @brief Defines the SudokuChecker class.
* @author Nikola Jolovic
* @date 26.12.2023.
*/

#pragma once

#include <bitset>
#include "../Sudoku/Board.hpp"
#include "../Constants.hpp"

namespace Checker{
	/**
	* @brief Sudoku checker class with board validation utilities.
	*/
	class SudokuChecker{
	public:
		/**
		* @brief Returns true if the board setup is valid. The setup is considered valid if the 3 rules of Sudoku are satisfied.
		* @param board The board to be validated.
		*/
		bool isValid(const Sudoku::Board& board);

		/**
		* @brief Returns true if the board is a correct solution to the start_board. Sets correct_values, incorrect_values and empty_cells to their respective counts.
		* @param board The board with the solution to be validated.
		* @param start_board The starting configuration of the board.
		* @correct_values Reference to the variable where the number of correctly placed values should be saved.
		* @incorrect_values Reference to the variable where the number of incorrectly placed values should be saved.
		* @empty_cells Reference to the variable where the number of cells that are left empty should be saved.
		*/
		bool isSolved(
			const Sudoku::Board& board, const Sudoku::Board& start_board,
			int& correct_values, int& incorrect_values, int& empty_cells
		) const;
	private:
		std::bitset<Constants::BOARD_SIZE> valueSet;
	};
}