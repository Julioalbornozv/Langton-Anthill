#pragma once

#include <GLFW/glfw.3>
#include <Tile.h>
#include <map>
#include <string>

class Color_Generator{
public:
	Color_Generator(Parser config);
	~Color_Generator();
	
	void load();
	void save();
	void random_palette(unsigned int n);
	void generate_colors();
	
	int** palette;	//!!
	
private:
	unsigned int size;
	unsigned int base;
	std::string interp;
	bool shuffle;
	bool write;
	std::string scheme;
	
	int** fill_palette(); //!!
	};
	
class Tile;
class Tile_Generator{
public:
	Tile_Generator(Parser config);
	~Tile_Generator();
	
	int** form();
	int** reset(int** colors);
	int* construct(int** colors);
	
	std::map<std::string, Tile> types;
	
private:
	unsigned int scale;
	std::string shape;
	
	
};