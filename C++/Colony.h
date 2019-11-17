#pragma once

class Colony{
public:
	Colony(Parser config, Tile tile);
	~Colony();
	
	void load_ants(char* path);
	void save_ants(char* path);
	std::string random_ruleset();
	
	Ant ants[];
	
private:
	unsigned int screen;
	std::string def_rule;
	std::string sym;
	unsigned int length;
	bool save;
	Tile Ttype;
	};