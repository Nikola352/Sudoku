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
		* @brief Returns true if the board is a correct solution to the start_board. Sets \p correct_values, \p incorrect_values and \p empty_cells to their respective counts.
		* 
		* @details Returns true if the \p board is a correct solution to the \p start_board, false otherwise. 
		Sets \p correct_values, \p incorrect_values and \p empty_cells to their respective counts. 
		Incorrect value count is defined as the number of cells that have a same-value neighbour + the number of cells that don't match the start_board.
		* 
		* @param board The board with the solution to be validated.
		* @param start_board The starting configuration of the board.
		* @param correct_values Reference to the variable where the number of correctly placed values should be saved.
		* @param incorrect_values Reference to the variable where the number of incorrectly placed values should be saved.
		* @param empty_cells Reference to the variable where the number of cells that are left empty should be saved.
		*/
		bool isSolved(
			const Sudoku::Board& board, const Sudoku::Board& start_board,
			int& correct_values, int& incorrect_values, int& empty_cells
		) const;
	private:
		std::bitset<Constants::BOARD_SIZE> valueSet;
	};
}