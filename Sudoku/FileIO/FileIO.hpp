/**
 * @file FileIO.hpp
 * @brief Defines functions for loading and saving boards to files.
 * @author Nikola Jolovic
 * @date 25.12.2023.
 */

#pragma once

#include <string>
#include "../Sudoku/Board.hpp"

/**
 * @brief Contains functions for loading and saving boards to files.
 */
namespace FileIO{
    /**
     * @brief Loads a board from a file.
     * 
     * @param filename Path to the file.
     * @param board Board to load the data into.
     */
	void loadFromFile(std::string filename, Sudoku::Board& board);

    /**
     * @brief Saves a board to a file.
     * 
     * @param filename Path to the file.
     * @param board Board to save.
     */
	void saveToFile(std::string filename, const Sudoku::Board& board);
}