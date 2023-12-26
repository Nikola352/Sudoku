/**
 * @file Menu.cpp
 * @brief Utilities for game UI through stdin and stdout.
 * @author Nikola Jolovic
 * @date 26.12.2023
 */

#include <iostream>
#include "Menu.hpp"

void Menu::printWelcomeMessage(){
	std::cout << "Welcome to Sudoku!\n\n";
}

bool Menu::promptGeneratorIsUser(){
	std::cout << "Would you like to load puzzle from file (F) or to have it generated by the computer (C)? (F/C) ";
	char mode;
	std::cin >> mode;
	return (mode == 'F' || mode == 'f');
}

bool Menu::promptSolverIsUser(){
	std::cout << "Would you like to load solution from file (F) or to have it solved by the computer (C)? (F/C) ";
	char mode;
	std::cin >> mode;
	return (mode == 'F' || mode == 'f');
}

void Menu::printGameInfo(bool is_valid, int correct_values, int incorrect_values, int empty_cells, int round_number) {
	std::cout << "Round number: " << round_number << '\n';
	if(is_valid){
		std::cout << "The solution is valid!\n";
	} else {
		std::cout << "The solution is NOT valid!\n";
	}
	std::cout << "The number of incorrectly placed digits: " << incorrect_values << '\n';
	std::cout << "The number of missing digits: " << empty_cells << '\n';
	std::cout << "The number of correctly placed digits: " << correct_values << '\n';
}

bool Menu::promptGameExit(){
	std::cout << "Would you like to play again? (Y/n) ";
	char ans;
	std::cin >> ans;
	return !(ans == 'Y' || ans == 'y');
}

void Menu::printInputError(){
	std::cout << "The provided board is not valid.\n";
}