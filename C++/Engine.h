/***
 * @file Engine.h
 * OpenGL rendering loop class
 */
// Copyright 2019 by Julio Albornoz <gatalegath@protonmail.com>
// The License.txt file describes the conditions under which this
// software may be distributed.

#pragma once
#include <GLFW/glfw.3>
#include "Parameters.h"
#include "Colony.h"
#include "Color_Generator.h"
#include "Tile_Generator.h"
#include "Tile.h"
#include <unordered_map>

class Engine{
	/***
	 * Class concerning simulation rendering and user interaction
	 */
public:
	Engine(Config* config, Tile* tile);
	void run(Colony* Anthill, Color_Generator* CGen, Tile_Generator* TGen);
	void render_tiles(std::unordered_map<int[2], int>* map);
	
private:
	int width, height;
	};