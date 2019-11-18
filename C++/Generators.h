/***
 * @file Generators.h
 * Color and Tile factories
 */
// Copyright 2019 by Julio Albornoz <gatalegath@protonmail.com>
// The License.txt file describes the conditions under which this software may be distributed.

#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Tile.h"
#include "Parameters.h"
#include <map>
#include <functional>
#include <string>

class Color_Generator{
	/***
	* Class responsible of creating the color palette used by the program
	* 
	* @param config: Configuration parameters
	* 
	* @field size: Ruleset length
	* @field base: Number of colors used to generate the colors
	* @field interp: Color interpolation method
	* @field shuffle: Determines if the generated colors are shuffled after generation
	* @field save: Determines if generated data is saved after the simulation
	* @field: palette, List of colors values for each tile (0-255)
	*/
public:
	Color_Generator(Config* config);
	~Color_Generator();
	
	void load();
	void save();
	void random_palette(unsigned int n);
	void generate_colors();
	
	glm::vec3* palette;
	
private:
	unsigned int size;
	unsigned int base;
	std::string interp;
	bool shuffle;
	bool write;
	std::string scheme;
	
	glm::vec3* fill_palette();
	};
	
class Tile;
class Tile_Generator{
	/***
	 * Class responsible of loading the requested tile type and render it when needed. 
	 * When adding a new tile shape, the self.types dictionry must be updated with the 
	 * Tile name and constructor.
	 * 	
	 * @param config: Config object containing starting parameters
	 * 
	 * @field scale: Tile scale factor
	 * @field shape: Requested tile shape
	 * @field types: Dictionary containing the currently available Tile object types 
	 *               and their associated names
	 * @field template: Generic tile which is given to other objects as a template
	 */
public:
	Tile_Generator(Config* config);
	
	Tile* generic;
	
	Tile* form();
	unsigned int* reset(glm::vec3** colors, int size);
	unsigned int* construct(glm::vec3** colors, int size);
	
private:
	unsigned int scale;
	std::string shape;
	
};