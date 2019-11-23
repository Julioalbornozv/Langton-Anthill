/***
 * @file Colony.h
 * Ant Management class
 */
// Copyright 2019 by Julio Albornoz <gatalegath@protonmail.com>
// The License.txt file describes the conditions under which this software may be distributed.

#pragma once
#include "Parameters.h"
#include "Tile.h"
#include "Ant.h"
#include <fstream>
#include <vector>
#include <string>

class Colony{
public:
	Colony(Config* config, Tile* tile);
	~Colony();
	
	void load_ants(std::string path = "ants.txt");
	void save_ants(std::string path = "save/ants.txt");
	std::string random_ruleset();
	
	std::vector<Ant>* ants;
	
private:
	unsigned int screen[2];
	std::string def_rule;
	std::string sym;
	unsigned int length;
	bool save;
	Tile* Ttype;
	};