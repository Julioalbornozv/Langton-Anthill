/***
 * @file Engine.h
 * OpenGL rendering loop class
 */
// Copyright 2019 by Julio Albornoz <gatalegath@protonmail.com>
// The License.txt file describes the conditions under which this
// software may be distributed.

#pragma once
#include <GLFW/glfw3.h>
#include "Parameters.h"
#include "Colony.h"
#include "Generators.h"
#include "Tile.h"
#include <unordered_map>
#include <map>
#include <utility> //Pairs
#include <winuser.h>

class Engine{
	/***
	 * Class concerning simulation rendering and user interaction
	 */
public:
	Engine(Config* config, Tile* tile);
	void run(Colony* Anthill, Color_Generator* CGen, Tile_Generator* TGen);
	void render_tiles(std::map<std::pair<int, int>, int>* map);
	
private:
	int width, height;
	GLFWwindow* window;
	};