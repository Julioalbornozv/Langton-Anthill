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
#include <unordered_map>
#include <functional>
#include <string>
#include <sstream>
#include <vector>

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
	void load(std::string path = "colors.txt");
	void save(std::string path = "save/colors.txt");
	void random_palette(unsigned int n);
	void generate_colors();
	unsigned int size;
	
	std::vector<glm::vec3>* palette;
	bool write;
	
private:
	unsigned int base;
	std::string interp;
	bool shuffle;
	std::string scheme;
	
	std::vector<glm::vec3>* fill_palette();
	void linspace(glm::vec3 A, glm::vec3 B, int num, std::vector<glm::vec3>* caret);
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
	int* reset(std::vector<glm::vec3>* colors);
	int* construct(std::vector<glm::vec3>* colors);
	
private:
	unsigned int scale;
	std::string shape;
	
};