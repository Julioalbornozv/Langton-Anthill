/***
 * @file Colony.cpp
 * Ant colony implementation
 */
// Copyright 2019 by Julio Albornoz <gatalegath@protonmail.com>
// The License.txt file describes the conditions under which this software may be distributed.

#include "Colony.h"
#include <sstream>
#include <time.h>

Colony::Colony(Config* config, Tile* tile){
	screen[0] = config->DWidth;
	screen[1] = config->DHeight;
	
	def_rule = config->def_rule;
	sym = config->symbols;
	length = config->length;
	save = config->Rsave;
	
	Ttype = tile;
	
	if (def_rule.compare("RANDOM") == 0){
		def_rule = random_ruleset();
		}
		
	load_ants();
	}
	
Colony::~Colony(){
	delete ants;
	}
	
void Colony::load_ants(std::string path){
	/***
	* Loads ant data from a txt file
	* 	
	* @param path: File path to be used
	*/ 
	std::ifstream file(path);	//File content
	std::string line;
	
	srand (time(NULL));
	std::vector<Ant>* insects = new std::vector<Ant>; 
	while (std::getline(file, line)){	//Read entire line
		std::stringstream linestream(line);
		
		std::string buffer;
		int X, Y, dir;		// Move parameters to an Ant factory
		
		//X position
		std::getline(linestream, buffer, '\t');		//Refactor this block
		if (buffer.compare("R") == 0){
			X = rand() % (screen[0] - 1) + 1;
			}
		else{
			X = std::stoi(buffer);
			}
			
		buffer.clear();
		
		//Y position
		std::getline(linestream, buffer, '\t');		//Refactor this block
		if (buffer.compare("R") == 0){
			Y = rand() % (screen[1] - 1) + 1;
			}
		else{
			Y = std::stoi(buffer);
			}
			
		buffer.clear();
		
		//Ant orientation
		std::getline(linestream, buffer, '\t');		//Refactor this block
		if (buffer.compare("R") == 0){
			int max = Ttype->directions.size();
			dir = rand() % max;
			}
		else{
			dir = std::stoi(buffer);
			}
		
		buffer.clear();
		
		//Ant ruleset
		if (linestream.eof()){			//Uses default ruleset
			buffer = def_rule;
			}
		
		std::getline(linestream, buffer);	//4th column
		if (buffer.compare("RANDOM") == 0){
			buffer = random_ruleset();
			}
		
		// Initializes Ant
		Ant bug = Ant(X * Ttype->X, Y * Ttype->Y, dir, buffer, Ttype);
		insects->push_back(bug);
		}
		
	ants = insects;
	file.close();
	
	if (save){
		save_ants("save/ants.txt");
		}
	}

void Colony::save_ants(std::string path){
	/***
	* Saves data of generated ants in a backup txt file
	* 	
	* @param path: Location of the backu
	*/
	std::ofstream file(path);	//File content
	std::vector<Ant> bugs = *ants;
	
	for (unsigned int i = 0; i < bugs.size(); i++){
		Ant ant = bugs[i];
		file << ant.pos[0]/Ttype->X << "\t" << ant.pos[1]/Ttype->Y << "\t" << ant.dir << "\t" << ant.ruleset << "\n";	
		}
	file.close();
	}

std::string Colony::random_ruleset(){
	/***
	* Generates a random set of instructions from the given specifications
	* 
	* @return	String containing the new ruleset
	* 
	*/
	srand (time(NULL));
	std::string Rrule;
	for (unsigned int i = 0; i < length; i++){
		int ch = rand() % sym.size();
		Rrule += sym[ch];
		}
	return Rrule;
	}
	
