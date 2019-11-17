#include "Parameters.h"
#include <string>
#include <windows.h>

Config::Config(){
	/* [WINDOWS] Parses configuration file "config.ini" and saves data in 
	 * a Config object.
	 
	 * TODO: Cleanup code
	 */
	 
	_TCHAR buffer[10];
	
	//[Display]
	this->DWidth = GetPrivateProfileInt("Display", "WIDTH", 0, ".\\config.ini");
	this->DHeight = GetPrivateProfileInt("Display", "HEIGHT", 0, ".\\config.ini");
	
	//[Color]
	
	this->base = GetPrivateProfileInt("Color", "BASE", 2, ".\\config.ini");
	
	GetPrivateProfileString("Color","SCHEME", "LOAD", buffer, sizeof(buffer) / sizeof(buffer[0]),".\\config.ini");
	this->scheme = buffer;
	
	GetPrivateProfileString("Color","INTERPOLATION", "NONE", buffer, sizeof(buffer) / sizeof(buffer[0]),".\\config.ini");
	this->interp = buffer;
	
	GetPrivateProfileString("Color","SHUFFLE", "YES", buffer, sizeof(buffer) / sizeof(buffer[0]),".\\config.ini");
	strcmp(buffer, "YES") ? this->shuffle = false : this->shuffle = true;
	
	GetPrivateProfileString("Color","SAVE", "YES", buffer, sizeof(buffer) / sizeof(buffer[0]),".\\config.ini");
	strcmp(buffer, "YES") ? this->Csave = false : this->Csave = true;
	
	//[Ruleset]
	this->length = GetPrivateProfileInt("Ruleset", "LENGTH", 2, ".\\config.ini");
	
	GetPrivateProfileString("Ruleset","SYMBOLS", "LR", buffer, sizeof(buffer) / sizeof(buffer[0]),".\\config.ini");
	this->symbols = buffer;
	
	int buff_size;
	if (this->length > 7){
		buff_size = this->length;
		}
	else{
		buff_size = 7; //RANDOM option
		}
		
	_TCHAR rule_buf[buff_size];
	
	GetPrivateProfileString("Ruleset","DEFAULT", "LR", rule_buf, sizeof(rule_buf) / sizeof(rule_buf[0]),".\\config.ini");
	this->def_rule = rule_buf;
	
	GetPrivateProfileString("Ruleset","SAVE", "YES", buffer, sizeof(buffer) / sizeof(buffer[0]),".\\config.ini");
	strcmp(buffer, "YES") ? this->Rsave = false : this->Rsave = true;
	
	//[Tile]
	this->scale = GetPrivateProfileInt("Tile", "SCALE", 5, ".\\config.ini");
	
	GetPrivateProfileString("Tile","SHAPE", "SQUARE", buffer, sizeof(buffer) / sizeof(buffer[0]),".\\config.ini");
	this->shape = buffer;
	}
	
