#pragma once
#include <string>

class Config{
public:
	// Display
	int DHeight, DWidth;	// Screen dimensions
	
	//Color
	int base;		// Number of colors used for palette generation
	std::string scheme;	// Color Generator mode
	std::string interp;	// Color Generator interpolation method
	bool shuffle;	// If true, color palette is shuffled after generation
	bool Csave;	// If true, save data in "save/colors.txt"
	
	//Ruleset
	int length;			// Ruleset size
	std::string symbols;		// Instructions used when generating a ruleset
	std::string def_rule;	// Default Ruleset used by all ants
	bool Rsave;		// If true, save data in "save/ants.txt
	
	//Tile
	int scale;		// Scale factor
	std::string shape;	// Tile shape (SQUARE or HEXAGON)
	
	Config();
	};