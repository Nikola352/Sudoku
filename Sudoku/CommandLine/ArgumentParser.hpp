/**
 * @file ArgumentParser.hpp
 * @brief Parses command line arguments and stores them in a class.
 * @author Nikola Jolovic
 * @date 26.12.2023 
 */

#pragma once

#include <vector>
#include <string>
#include "../Generator/SudokuGenerator.hpp"

namespace CommandLine{
    /**
     * @brief Parses command line arguments and stores them in a class.
     */
	class ArgumentParser{
	public:
        /**
         * @brief Construct a new Argument Parser object
         * 
         * @param argc Number of arguments
         * @param argv Array of arguments
         */
		ArgumentParser(int argc, char *argv[]);

        /**
         * @brief Parses the arguments and stores them in a class.
         * @throw std::invalid_argument if the arguments are invalid
         */
		void parse();

        /**
         * @brief Checks if the arguments are valid.
         * @return true if the arguments are valid, false if they are not valid or if they have not been parsed yet
         */
		bool isValid();

        /**
         * @brief Gets the start filename.
         * @return std::string the start filename
         * @throw std::invalid_argument if the arguments are invalid or if they have not been parsed yet
         */
		std::string getStartFilename();

        /**
         * @brief Gets the solution filename.
         * @return std::string the solution filename
         * @throw std::invalid_argument if the arguments are invalid or if they have not been parsed yet
         */
		std::string getSolutionFilename();

        /**
         * @brief Gets the difficulty.
         * @return Sudoku::Difficulty the difficulty
         * @throw std::invalid_argument if the arguments are invalid or if they have not been parsed yet
         */
		Sudoku::Difficulty getDifficulty();

        /**
         * @brief Checks if the unique flag is passed.
         * @return true if the unique flag is passed, false otherwise
         * @throw std::invalid_argument if the arguments are invalid or if they have not been parsed yet
         */
		bool getUnique();

	private:
		std::vector<std::string> args; /**<  Command line arguments */

		bool is_valid; /**<  Flag that indicates if the arguments are valid */
		std::vector<std::string> filenames; /**<  Filenames for start and solution boards. Should contain exactly 2 values after a valid parse. */
		Sudoku::Difficulty difficulty; /**<  Difficulty for SudokuGenerator */
		bool unique_solution; /**<  Flag that indicates if the unique flag is passed */
	};
}