#include "Parameters.h"
/***
 * @file Parameters.cpp
 * Ini File parsing implementation
 */
// Copyright 2019 by Julio Albornoz <gatalegath@protonmail.com>
// The License.txt file describes the conditions under which this
// software may be distributed.

#include "Parameters.h"

Config::Config(){
	/*** 
	 * [WINDOWS] Parses configuration file "config.ini" and saves data in 
	 * a Config object.
	 */
	
	//[Display]
	getBool(&fullscreen, 10, "Display", "FULLSCREEN", "YES");
	DWidth = GetPrivateProfileInt("Display", "WIDTH", 50, ".\\config.ini");
	DHeight = GetPrivateProfileInt("Display", "HEIGHT", 50, ".\\config.ini");
	
	//[Grid]
	getBool(&fullscreen, 10, "Grid", "ADJUST", "YES");
	GWidth = GetPrivateProfileInt("Grid", "WIDTH", 50, ".\\config.ini");
	GHeight = GetPrivateProfileInt("Grid", "HEIGHT", 50, ".\\config.ini");
	
	//[Color]
	base = GetPrivateProfileInt("Color", "BASE", 2, ".\\config.ini");
	getString(&scheme, 10, "Color", "SCHEME", "LOAD");
	getString(&interp, 10, "Color", "INTERPOLATION", "NONE");
	getBool(&shuffle, 10, "Color", "SHUFFLE", "YES");
	getBool(&Csave, 10, "Color", "SAVE", "YES");
	
	//[Ruleset]
	length = GetPrivateProfileInt("Ruleset", "LENGTH", 2, ".\\config.ini");
	getString(&symbols, 10, "Ruleset", "SYMBOLS", "L");
	
	int buff_size;
	(length > 7) ? buff_size = length+1 : buff_size = 7;
		
	getString(&def_rule, buff_size, "Ruleset", "DEFAULT", "LR");
	getBool(&Rsave, 10, "Ruleset", "SAVE", "YES");

	//[Tile]
	scale = GetPrivateProfileInt("Tile", "SCALE", 5, ".\\config.ini");
	getString(&shape, 10, "Tile", "SHAPE", "SQUARE");
	
	}
	
void Config::getString(std::string* target, int size, LPCTSTR section, LPCTSTR setting, LPCTSTR fail_state, LPCTSTR file){
	/***
	* Recover string from config file using GetPrivateProfileString method
	*/
	_TCHAR buffer[size];
	GetPrivateProfileString(section, setting, fail_state, buffer, size, file);
	*target = buffer;
	}

void Config::getBool(bool* target, int size, LPCTSTR section, LPCTSTR setting, LPCTSTR fail_state, LPCTSTR file){
	/***
	* Recover bool from config file using GetPrivateProfileString method
	*/
	_TCHAR buffer[size];
	GetPrivateProfileString(section, setting, fail_state, buffer, size, file);
	strcmp(buffer, "YES") ? *target = false : *target = true;
	}