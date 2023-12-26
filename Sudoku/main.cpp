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
#include "CommandLine\ArgumentParser.hpp"

int main(int argc, char *argv[])
{
    CommandLine::ArgumentParser cmdArgParser(argc, argv);
    try{
        cmdArgParser.parse();
    }
    catch(const std::invalid_argument& e){
        std::cerr << e.what() << '\n';
        std::cerr << "Usage: " << argv[0] << " [-u] [-d <e|m|h>] <start_filename> <solution_filename>\n";
        return 1;
    }

    Sudoku::Sudoku game(
        cmdArgParser.getStartFilename(), cmdArgParser.getSolutionFilename(),
        cmdArgParser.getDifficulty(), cmdArgParser.getUnique()
    );

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
