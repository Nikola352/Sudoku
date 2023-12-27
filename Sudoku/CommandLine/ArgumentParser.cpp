/**
 * @file ArgumentParser.cpp
 * @brief Implement command line parsing logic.
 * @author Nikola Jolovic
 * @date 26.12.2023 
 */

#include <stdexcept>
#include <filesystem>
#include <fstream>
#include "ArgumentParser.hpp"
#include "../Generator/SudokuGenerator.hpp"

namespace CommandLine{
	ArgumentParser::ArgumentParser(int argc, char *argv[])
		: args(argv+1, argv+argc), is_valid(false), unique_solution(false), difficulty(Sudoku::Difficulty::MEDIUM) {}

	inline bool file_exists(const std::string& filename) {
		std::ifstream f(filename.c_str());
		return f.good();
	}

	void ArgumentParser::parse(){
		this->unique_solution = false;
		this->filenames.clear();
		for(int i=0; i<this->args.size(); i++){
			const std::string& arg = args[i];
			if(arg[0] == '-'){
				if(arg.length() != 2){
					this->is_valid = false;
					throw std::invalid_argument(std::string("Invalid command line argument '") + arg + std::string("'."));
				}
				switch(arg[1])
				{
				case 'u':
					this->unique_solution = true;
					break;
				case 'd':
				{
					i++;
					switch(this->args[i][0])
					{
					case 'e':
						this->difficulty = Sudoku::Difficulty::EASY;
						break;
					case 'm':
						this->difficulty = Sudoku::Difficulty::MEDIUM;
						break;
					case 'h':
						this->difficulty = Sudoku::Difficulty::HARD;
						break;
					default:
						this->is_valid = false;
						throw std::invalid_argument("Invalid option for difficulty. Available options are: 'e' - Easy 'm' - Medium, 'h' - Hard");
						break;
					}
					break;
				}
				default:
					this->is_valid = false;
					throw std::invalid_argument(std::string("Invalid option: '") + arg + std::string("'."));
					break;
				}
			} else if(!file_exists(arg)){
				this->is_valid = false;
				throw std::invalid_argument(std::string("No such file: '") + arg + std::string("'."));
			} else {
				this->filenames.push_back(arg);
			}
		}
		if(this->filenames.size() < 2){
			this->is_valid = false;
			throw std::invalid_argument("Please provide 2 filenames.");
		} else if(this->filenames.size() > 2){
			this->is_valid = false;
			throw std::invalid_argument("Too many filenames provided.");
		}
		this->is_valid = true;
	}

	bool ArgumentParser::isValid(){
		return this->is_valid;
	}

	std::string ArgumentParser::getStartFilename(){
		if(!this->is_valid){
			throw std::invalid_argument("Unhandled invalid command line arguments list.");
		}
		return this->filenames[0];
	}

	std::string ArgumentParser::getSolutionFilename(){
		if(!this->is_valid){
			throw std::invalid_argument("Unhandled invalid command line arguments list.");
		}
		return this->filenames[1];
	}

	Sudoku::Difficulty ArgumentParser::getDifficulty(){
		if(!this->is_valid){
			throw std::invalid_argument("Unhandled invalid command line arguments list.");
		}
		return this->difficulty;
	}

	bool ArgumentParser::getUnique(){
		if(!this->is_valid){
			throw std::invalid_argument("Unhandled invalid command line arguments list.");
		}
		return this->unique_solution;
	}
}