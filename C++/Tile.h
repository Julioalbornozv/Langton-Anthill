#pragma once
#include <map>
#include <string>

class Tile{
public:
	int scale, X, Y;
	std::map<int, int[2]> directions;
	std::map<std::string, int> offset;
	virtual compile(std::vector<float[3]> color);
	};
	
class Square_Tile : Tile;
class Hexagon_Tile : Tile;