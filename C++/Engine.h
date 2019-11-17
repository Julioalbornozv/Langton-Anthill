#pragma once
#include <GLFW/glfw.3>
#include <map>
#include <string>

class Engine{
public:
	Engine(Parser config, Tile tile);
	~Engine();
	void run(Colony Anthill, Color_Generator CGen, Tile_Generator TGen);
	void render_tiles(std::map<int[2], int>);
	
private:
	int width, height;
	};