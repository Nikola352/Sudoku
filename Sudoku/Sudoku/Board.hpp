/**
* @file Board.hpp
* @brief Defines Board class.
* @author Nikola Jolovic
* @date 25.12.2023
*/

#pragma once

#include <iostream>
#include <bitset>
#include "../Constants.hpp"

using Constants::BOARD_SIZE;

namespace Sudoku {
    /**
     * @brief Class that represents a Sudoku board state.
     */
    class Board {
    public:
        /**
         * @brief Default constructor. Creates an empty Sudoku board.
         */
        Board();

        /**
         * @brief Constructor. Creates a Sudoku board from the given char matrix.
         * @param board The 2D char array to create the Sudoku board from.
         */
        Board(const char board[BOARD_SIZE][BOARD_SIZE]);

        /**
         * @brief Copy constructor. Performs a deep copy of the Sudoku board.
         * @param other The Sudoku board to copy.
         */
        Board(const Board& other);

        /**
         * @brief Assignment operator. Constructs the Sudoku board with the copy of the contents of another board.
         * @param other The Sudoku board to copy.
         * @return A reference to the modified Sudoku board.
         */
        Board& operator=(const Board& other);

        /**
         * @brief Overloaded indexing operator for non-constant objects. Provides access to the specified row of the Sudoku board.
         * @param rowIdx The index of the row to access.
         * @return A pointer to the specified row of the Sudoku board.
         */
        char* operator[](int rowIdx);

        /**
         * @brief Overloaded indexing operator for constant objects. Provides read-only access to the specified row of the Sudoku board.
         * @param rowIdx The index of the row to access.
         * @return A constant pointer to the specified row of the Sudoku board.
         */
        const char* operator[](int rowIdx) const;

        /**
         * @brief Input stream operator. Reads a Sudoku board from the input stream.
         * @param in The input stream.
         * @param board The Sudoku board to read into.
         * @return A reference to the input stream after reading the Sudoku board.
         */
        friend std::istream& operator>>(std::istream& in, Board& board);

        /**
         * @brief Output stream operator. Writes a Sudoku board to the output stream.
         * @param out The output stream.
         * @param board The Sudoku board to write.
         * @return A reference to the output stream after writing the Sudoku board.
         */
        friend std::ostream& operator<<(std::ostream& out, const Board& board);

        /**
         * @brief Static method to get the block number based on row and column indices.
         * @param rowIdx The index of the row.
         * @param colIdx The index of the column.
         * @return The block number corresponding to the given row and column indices.
         */
        static int getBlockNum(int rowIdx, int colIdx);

    private:
        char board[BOARD_SIZE][BOARD_SIZE]; /**< 2D array representing the Sudoku board. */
    };
}
