/***
 * @file Colony.cpp
 * Ant colony implementation
 */
// Copyright 2019 by Julio Albornoz <gatalegath@protonmail.com>
// The License.txt file describes the conditions under which this software may be distributed.

#include "Colony.h"
#include <sstream>
Colony::Colony(Config* config, Tile* tile){
	this->screen[0] = config->width;
	this->screen[1] = config->height;
	
	this->def_rule = config->def_rule;
	this->sym = config->symbols;
	this->length = config->length;
	this->save = config->RSave;
	
	this->Ttype = tile;
	
	if (this->def_rule.compare("RANDOM") == 0){
		this->def_rule = this->random_ruleset();
		}
	}
	
void Colony::load_ants(std::string path){
	/***
	* Loads ant data from a txt file
	* 	
	* @param path: File path to be used
	*/ 
	std::ifstream file(path);	//File content
	std::string line;
	
	while std::getline(file, line){	//Read entire line
		std::stringstream linestream(line);
		
		std::string buffer;
		int X, Y, dir;		// Move parameters to an Ant factory
		
		//X position
		std::getline(linestream, buffer, '\t');		//Refactor this block
		if (buffer.compare('R') == 0){
			X = rand() % (this->screen[0] - 1) + 1
			}
		else{
			X = std::stoi(X);
			}
			
		buffer.clear();
		
		//Y position
		std::getline(linestream, buffer, '\t');		//Refactor this block
		if (buffer.compare('R') == 0){
			Y = rand() % (this->screen[1] - 1) + 1
			}
		else{
			Y = std::stoi(Y);
			}
			
		buffer.clear();
		
		//Ant orientation
		std::getline(linestream, buffer, '\t');		//Refactor this block
		if (buffer.compare('R') == 0){
			int max = this->Ttype->directions.size();
			dir = rand() % max
			}
		else{
			dir = std::stoi(X);
			}
		
		buffer.clear();
		
		//Ant ruleset
		if (linestream.eof()){			//Uses default ruleset
			buffer = this->def_rule;
			}
		
		std::getline(linestream, buffer);	//4th column
		if (buffer.compare('RANDOM'){
			buffer = std::random_ruleset();
			}
		
		// Initializes Ant
		ants.push_back(new Ant(X, Y, dir, buffer, this->Ttype);
		}
	file.close();
	
	if (this->save){
		this->save_ants("save/ants.txt");
		}
	}

void save_ants(std::string path){
	/***
	* Saves data of generated ants in a backup txt file
	* 	
	* @param path: Location of the backu
	*/
	std::ofstream file(path);	//File content
	
	for (auto &this->ants : ant){
		file << ant->pos[0]/this->Ttype->X << "\t" << ant->pos[1]/this->Ttype->Y << "\t" << ant->dir << "\t" << ant->ruleset << "\n";	
		}
	file.close();
	}

std::string random_ruleset(){
	/***
	* Generates a random set of instructions from the given specifications
	* 
	* @return	String containing the new ruleset
	* 
	*/
	
	std::string Rrule;
	for (int i = 0; i < this->length; i++){
		int ch = rand() % this->sym.size();		//FIX: This can cause an error if the symbols given are unordered!!!
		Rrule += this[sym];
		}
	return Rrule;
	}
	
