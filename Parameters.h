/***
 * @file Parameters.h
 * Ini File parsing class
 */
// Copyright 2019 by Julio Albornoz <gatalegath@protonmail.com>
// The License.txt file describes the conditions under which this
// software may be distributed.

#pragma once
#include <string>
#include <windows.h>

class Config{
public:
	//Display
	bool fullscreen	;				// Fullscreen option
	unsigned int DWidth, DHeight;	// Screen dimensions
	
	//Grid
	bool adjust;					// Grid size == Display Size 
	unsigned int GWidth, GHeight;	// Board Dimensions
	//Color
	unsigned int base;	// Number of colors used for palette generation
	std::string scheme;		// Color Generator mode
	std::string interp;		// Color Generator interpolation method
	bool shuffle;			// If true, color palette is shuffled after generation
	bool Csave;			// If true, save data in "save/colors.txt"
	
	//Ruleset
	unsigned int length;	// Ruleset size
	std::string symbols;	// Instructions used when generating a ruleset
	std::string def_rule;	// Default Ruleset used by all ants
	bool Rsave;			// If true, save data in "save/ants.txt
	
	//Tile
	unsigned int scale;	// Scale factor
	std::string shape;		// Tile shape (SQUARE or HEXAGON)
	
	Config();
	
private:
	void getString(std::string* target , int size, LPCTSTR section, LPCTSTR setting, LPCTSTR fail_state, LPCTSTR file = ".\\config.ini");
	void getBool(bool* target , int size, LPCTSTR section, LPCTSTR setting, LPCTSTR fail_state, LPCTSTR file = ".\\config.ini");
	};