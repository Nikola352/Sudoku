/**
 * @file constants.hpp
 * @brief Global game constants.
 * @author Nikola Jolovic
 * @date 19.12.2023
 */

#pragma once

#include <map>

namespace Constants{
	const int BOARD_SIZE = 9;
	const int BLOCK_SIZE = 3;

	// characters that can be written to the board
	const char ALPHABET[BOARD_SIZE] ={'1', '2', '3', '4', '5', '6', '7', '8', '9'};

	// character that represents empty cell on the board
	const char EMPTY_CELL = 0;

	// index of each key in alphabet
	const std::map<char, int> KEY_IDX({
		{'1', 0},
		{'2', 1},
		{'3', 2},
		{'4', 3},
		{'5', 4},
		{'6', 5},
		{'7', 6},
		{'8', 7},
		{'9', 8},
	});
}