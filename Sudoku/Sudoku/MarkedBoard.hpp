/**
* @file MarkedBoard.hpp
* @brief Defines Board class.
* @author Nikola Jolovic
* @date 25.12.2023
*/

#pragma once

#include "Board.hpp"
#include <bitset>

namespace Sudoku {
    /**
     * @brief Class that represents a marked Sudoku board, with additional information about possible marks in each cell.
     */
    class MarkedBoard : public Board {
    public:
        /**
         * @brief Default constructor. Creates an empty marked Sudoku board.
         */
        MarkedBoard();

        /**
         * @brief Copy constructor. Constructs a marked Sudoku board with the copy of the contents of another board.
         * @param other The Sudoku board to copy.
         */
        MarkedBoard(const Board& other);

        /**
         * @brief Copy constructor. Performs a deep copy of the marked Sudoku board.
         * @param other The marked Sudoku board to copy.
         */
        MarkedBoard(const MarkedBoard& other);

        /**
         * @brief Assignment operator. Constructs a marked Sudoku board with the copy of the contents of another board.
         * @param other The Sudoku board to copy.
         * @return A reference to the modified marked Sudoku board.
         */
        MarkedBoard& operator=(const Board& other);

        /**
         * @brief Assignment operator. Performs a deep copy of the marked Sudoku board.
         * @param other The marked Sudoku board to copy.
         * @return A reference to the modified marked Sudoku board.
         */
        MarkedBoard& operator=(const MarkedBoard& other);

        std::bitset<BOARD_SIZE> rowSets[BOARD_SIZE]; /**< Array of bitsets representing possible marks for each row. */
        std::bitset<BOARD_SIZE> colSets[BOARD_SIZE]; /**< Array of bitsets representing possible marks for each column. */
        std::bitset<BOARD_SIZE> blockSets[BOARD_SIZE]; /**< Array of bitsets representing possible marks for each block. */

    private:
        /**
         * @brief Private method to calculate possible marks for each cell on the marked Sudoku board.
         */
        void calculateMarks();
    };
}
