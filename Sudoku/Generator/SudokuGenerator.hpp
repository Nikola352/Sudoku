/**
 * @file SudokuGenerator.hpp
 * @brief Defines the SudokuGenerator class.
 * @author Nikola Jolovic
 * @date 26.12.2023
 */

#pragma once

#include <random>
#include "../Sudoku/Board.hpp"
#include "../Sudoku/MarkedBoard.hpp"

namespace Sudoku{
    /**
     * @brief Difficulty levels of the generated Sudoku.
     */
	enum Difficulty{
		EASY, MEDIUM, HARD
	};

    /**
     * @brief Generates a Sudoku board.
     * 
     * Generates a Sudoku board with a given difficulty level and a given uniqueness.
     * The generated board is stored in the given Board object.
     */
	class SudokuGenerator{
	public:
        /**
         * @brief Default constructor.
         * 
         * Constructs a SudokuGenerator with default values (difficulty=MEDIUM, unique=true)
         */
		SudokuGenerator();

        /**
         * @brief Constructor.
         * 
         * Constructs a SudokuGenerator with given difficulty level and uniqueness.
         * 
         * @param difficulty Difficulty level of the generated Sudoku.
         * @param unique Indicates if the generated solution must be unique.
         */
		SudokuGenerator(Difficulty difficulty, bool unique);

        /**
         * @brief Fills the given Board with a random Sudoku solution.
         * 
         * Fills the given Board with a random Sudoku solution with a given difficulty level and uniqueness.
         * 
         * @param board The Board to be filled.
         */
		void generateBoard(Board& board);

        /**
         * @brief Sets the difficulty level for the Sudoku generation.
         * 
         * @param difficulty The new difficulty level.
         */
        void setDifficulty(Difficulty difficulty);

        /**
         * @brief Sets the uniqueness for the Sudoku generation.
         * 
         * @param unique True if the generated solution must be unique, false otherwise.
         */
        void setUnique(bool unique);

	private:
		bool unique; /**< Indicates if the generated solution must be unique. */
		Difficulty difficulty; /**< Difficulty level of the generated Sudoku. */

		std::mt19937 random_gen; /**< Random number generator. */

        
		int randomIndex();

        /**
         * @brief Fills the given Board with a random Sudoku solution.
         * 
         * @param board The Board to be filled.
         */
		void fillBoard(Board& board);

        /**
         * @brief Fills the given MarkedBoard with a random Sudoku solution.
         * 
         * Fills the given MarkedBoard with a random Sudoku solution starting from the given cell.
         * 
         * @param board The MarkedBoard to be filled.
         * @param rowIdx The row index of the cell to be filled.
         * @param colIdx The column index of the cell to be filled.
         * @return true if the board is filled, false otherwise.
         */
		bool fillBoardFrom(MarkedBoard& board, int rowIdx, int colIdx);

        /**
         * @brief Generates a Sudoku board with a not necessarily unique solution.
         * 
         * Generates a Sudoku board with a given difficulty level.
         * The generated board is stored in the given Board object.
         * The generated board does not necessarily have a unique solution.
         * 
         * @param board The Board to be filled.
         */
		void generate(Board& baord);

        /**
         * @brief Generates a Sudoku board with a unique solution.
         * 
         * Generates a Sudoku board with a given difficulty level.
         * The generated board is stored in the given Board object.
         * The generated board has a unique solution.
         * 
         * @param board The Board to be filled.
         */
		void generateUnique(Board& board);

        /**
         * @brief Determins if the number of solutions of the given MarkedBoard is 0, 1 or more than 1.
         * 
         * Counts the number of solutions of the given MarkedBoard starting from the given cell.
         * Returns the number of solutions if it is 0 or 1, or 2 if it is more than 1.
         * 
         * @param board The MarkedBoard to be counted.
         * @param rowIdx The row index of the cell to be counted.
         * @param colIdx The column index of the cell to be counted.
         * @return 0 if the board has no solution, 1 if it has a unique solution, 2 if it has more than 1 solution.
         */
		int solutionCount(MarkedBoard& board, int rowIdx, int colIdx);
	};
}