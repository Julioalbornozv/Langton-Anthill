/***
 * @file Engine.h
 * OpenGL rendering loop class
 */
// Copyright 2019 by Julio Albornoz <gatalegath@protonmail.com>
// The License.txt file describes the conditions under which this
// software may be distributed.

#pragma once

#include "Colony.h"
#include "Generators.h"
#include "Monitor.h"
#include <map>
#include <utility> //Pairs
#include <winuser.h>

class Config;
class Tile;
class GLFWwindow;
class Engine{
	/***
	 * Class concerning simulation rendering and user interaction
	 */
public:
	Engine(Config* config, Tile* tile, Monitor* monitor);
	void run(Colony* Anthill, Color_Generator* CGen, Tile_Generator* TGen);
	void render_tiles(std::map<std::pair<int, int>, int>* map);
	
private:
	int Dwidth, Dheight, Gwidth, Gheight;
	int* speed;
	GLFWwindow* window;
	
	void catchInput(Color_Generator* CG, Tile_Generator* TG);
	};