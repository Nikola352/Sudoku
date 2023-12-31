# Sudoku

A simple Sudoku game in C++.

## Gameplay
Names of the files for start board configuration and solution must be specified as command line arguments.
Optionally `-u` flag may be passed to guarantee a uniquely solvable Sudoku generation and `-d <e|m|h>` for determining generated board difficulty.

The cli prompts the user to either input the board through a file manually or have it auto-generated and saved to the start board file.

It then prompts the user to either solve the board manually and input solution through a file, or gane it solved automatically by the computer.

Finally, the computer validates the solution and outputs game statistics to the console.

The game can be repeated any number of times.

## Components
Core Sudoku logic is split into 3 main components: Generator, Solver and Checker.
Other utility components include Menu for application console interface, FileIO for file operations and ArgumentParser for command line argument parsing.

### Generator
`SudokuGenerator` class can be used to generate a random Sudoku puzzle. Three difficulty levels are available. I the command line argument `-u` is not specified, the puzzle is not guarenteed to be uniquely solvable.

The generator works by first randomly filling the whole board and removing values in a structured manner.

### Solver
`SudokuSolver` class implements a simple backtracking Sudoku solving algorithm.

### Checker
`SudokuChecker` class contains utility functions for board validation and solution validation.

## Testing
Unit tests are implemented using Google Test framework.

## Note
Other board dimensions can be produces by changing the `BOARD_SIZE` in `Constants.hpp`.
