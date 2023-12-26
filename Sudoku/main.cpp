/*
* @file main.cpp
* @brief Main entry to the application. Checks for command line arguments and starts the game loop.
* @author Nikola Jolovic
* @date 26.12.2023
*/

#include <iostream>
#include "Constants.hpp"
#include "Sudoku\Sudoku.hpp"
#include "Menu\Menu.hpp"
#include "FileIO\FileIO.hpp"

int main(int argc, char *argv[])
{
    if(argc != 3){
        std::cerr << "Usage: " << argv[0] << " [start_filepath] [solution_filepath]\n";
        return 1;
    }

    Sudoku::Sudoku game(argv[1], argv[2]);

    Menu::printWelcomeMessage();

    // the game loop
    while(true) {
        if(Menu::promptGeneratorIsUser()){
            if(!game.loadStartBoardFromFile()){
                Menu::printInputError();
                continue;
            }
        } else {
            game.generateStartBoard();
        }
        if(Menu::promptSolverIsUser()){
            game.loadSolvedBoardFromFile();
        } else {
            game.solve();
        }
        bool is_valid = game.validate();
        game.incrementRoundCounter();
        Menu::printGameInfo(
            is_valid,
            game.getCorrectValues(), game.getIncorrectValues(),
            game.getEmptyCells(), game.getRoundCount()
        );
        if(Menu::promptGameExit()) break;
    }

}
