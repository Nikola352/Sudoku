/**
 * @file Sudoku.hpp
 * @brief Defines Sudoku class that holds the game state.
 * @author Nikola Jolovic
 * @date 26.12.2023
 */

#pragma once

#include <string>
#include "../Constants.hpp"
#include "../Generator/SudokuGenerator.hpp"
#include "../Checker/SudokuChecker.hpp"
#include "../Solver/SudokuSolver.hpp"
#include "Board.hpp"

using Constants::BOARD_SIZE;

namespace Sudoku{
    /**
     * @brief Class that holds the game state.
     */
	class Sudoku{
	public:
        /**
         * @brief Constructor.
         * @param start_filename Path to the file where the start board is stored.
         * @param solution_filename Path to the file where the solution board is stored.
         */
		Sudoku(std::string start_filename, std::string solution_filename);

        /**
         * @brief Getter for round_counter.
         * @return Number of rounds played.
         */
		int getRoundCount();

        /**
         * @brief Increments round_counter.
         */
		void incrementRoundCounter();

        /**
         * @brief Getter for correct_values.
         * @return Number of correct values.
         */
		int getCorrectValues();

        /**
         * @brief Getter for incorrect_values.
         * @return Number of incorrect values.
         */
		int getIncorrectValues();

        /**
         * @brief Getter for empty_cells.
         * @return Number of empty cells.
         */
		int getEmptyCells();

        /**
         * @brief Loads start board from file.
         * 
         * @details Loads start board from this->start_filename file and checks if it is valid.
         * 
         * @return True if the board is valid, false otherwise.
         */
		bool loadStartBoardFromFile();

        /**
         * @brief Loads solution board from file.
         * 
         * @details Loads solution board from this->solution_filename file.
         */
		void loadSolvedBoardFromFile();

        /**
         * @brief Generates start board.
         * 
         * @details Generates start board and saves it to this->start_filename file.
         */
		void generateStartBoard();

        /**
         * @brief Solves the Sudoku.
         * 
         * @details Solves the Sudoku and saves the solution to this->solution_filename file.
         */
		void solve();

        /**
         * @brief Validates the game.
         * 
         * @details Validates the Sudoku game solution and updates correct_values, incorrect_values and empty_cells.
         * 
         * @return True if the game is valid (satisfies the 3 rules of Sudoku), false otherwise.
         */
		bool validate();
	private:
		int round_counter; /**< Number of rounds played. */
		int correct_values; /**< Number of cells with correct value. */
		int incorrect_values; /**< Number of cells with incorrect value. */
		int empty_cells; /**< Number of empty cells. */

		Board start_board; /**< Starting position of the board. */
		MarkedBoard game_board; /**< Game board. Will be filled with the solution. */

		std::string start_filename; /**< Path to the file where the start board is stored. */
		std::string solution_filename; /**< Path to the file where the solution board is stored. */

		Generator::SudokuGenerator generator; /**< Sudoku generator. */
		Checker::SudokuChecker checker; /**< Sudoku checker. */
		Solver::SudokuSolver solver; /**< Sudoku solver. */
	};
}