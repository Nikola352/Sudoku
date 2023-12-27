/**
 * @file Sudoku.cpp
 * @brief Implementation of the Sudoku class with the game logic.
 * @author Nikola Jolovic
 * @date 26.12.2023
 */

#include <string>
#include "Sudoku.hpp"
#include "../FileIO/FileIO.hpp"

namespace Sudoku {
	Sudoku::Sudoku(std::string start_filename, std::string solution_filename, Difficulty difficulty, bool unique_solution) 
		: round_counter(0), correct_values(0), incorrect_values(0), empty_cells(0),
		start_board(), game_board(),
		generator(difficulty, unique_solution), checker(), solver(),
		start_filename(start_filename), solution_filename(solution_filename)
	{}

	int Sudoku::getRoundCount() {
		return this->round_counter;
	}

	void Sudoku::incrementRoundCounter(){
		this->round_counter++;
	}

	int Sudoku::getCorrectValues(){
		return this->correct_values;
	}

	int Sudoku::getIncorrectValues(){
		return this->incorrect_values;
	}

	int Sudoku::getEmptyCells(){
		return this->empty_cells;
	}

	bool Sudoku::loadStartBoardFromFile(){
		FileIO::loadFromFile(this->start_filename, this->start_board);
		return this->checker.isValid(this->start_board);
	}

	void Sudoku::loadSolvedBoardFromFile(){
		FileIO::loadFromFile(this->solution_filename, this->game_board);
	}

	void Sudoku::generateStartBoard(){
		this->generator.generateBoard(this->start_board);
		FileIO::saveToFile(this->start_filename, this->start_board);
	}

	void Sudoku::solve() {
		this->solver.solve(this->start_board, this->game_board);
		FileIO::saveToFile(this->solution_filename, this->game_board);
	}

	bool Sudoku::validate() {
		return this->checker.isSolved(
			this->game_board, this->start_board,
			this->correct_values, this->incorrect_values, this->empty_cells
		);
	}
}