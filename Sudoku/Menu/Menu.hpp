/**
 * @file Menu.hpp
 * @brief Utilities for game UI through stdin and stdout.
 * @author Nikola Jolovic
 * @date 26.12.2023
 */

#pragma once

 /**
  * @namespace Menu
  * @brief Contains utilities for game UI through stdin and stdout.
  */
namespace Menu {
    /**
     * @brief Prints a welcome message.
     */
    void printWelcomeMessage();

    /**
     * @brief Prompts the user to answer whether the puzzle should be generated from the computer or loaded from a file.
     * @return true if the board should be loaded from a file.
     */
    bool promptGeneratorIsUser();

    /**
     * @brief Prompts the user to answer whether the puzzle solution should be solved by the computer or loaded from a file.
     * @return true if the board should be loaded from a file.
     */
    bool promptSolverIsUser();

    /**
     * @brief Prints game statistics after the game ends.
     * @param is_valid Set to true if the sudoku is correctly solved.
     * @param correct_values Number of board cells with correct values assigned.
     * @param incorrect_values Number of board cells with incorrect values assigned.
     * @param round_number The number of completed rounds.
     */
    void printGameInfo(bool is_valid, int correct_values, int incorrect_values, int empty_cells, int round_number);

    /**
     * @brief Prompts the user to confirm if they want to exit the game.
     * @return true if the user chooses to exit the game, false otherwise.
     */
    bool promptGameExit();

    /**
     * @brief Prints an error message in case of invalid input board values.
    */
    void printInputError();

    /**
     * @brief Prints an error message in case of an unsolvable puzzle.
    */
    void printUnsolvable();
}
