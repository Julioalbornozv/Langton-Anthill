/***
 * @file Tile_Generator.cpp
 * Tile factory
 */
// Copyright 2019 by Julio Albornoz <gatalegath@protonmail.com>
// The License.txt file describes the conditions under which this
// software may be distributed.

#include "Generators.h"

Tile_Generator::Tile_Generator(Config* config){
	scale = config->scale;
	shape = config->shape;
	
	generic = form();
	}
	
Tile* Tile_Generator::form(){
	/***
	 * Initializes a Tile object, if the shape requested is not known it 
	 * will raise an error.
	 */
	if (shape.compare("SQUARE") == 0){
		return new Square_Tile(scale);
		}
	else if (shape.compare("HEXAGON") == 0){
		return new Hexagon_Tile(scale);
		}	
	else{
		throw std::invalid_argument("Unknown tile shape");
		}
	}
	
void Tile_Generator::reset(std::vector<glm::vec3>* colors){
	/***
	 * Deletes previous Tile instances, creates a new set based on 
	 * the colors given.
	 * 
	 * @param colors: New colorset
	 * 
	 * @return New Tileset OpenGL ID list
	 */
	 glDeleteLists(1, colors->size());
	 construct(colors);
	}
	
void Tile_Generator::construct(std::vector<glm::vec3>* colors){
	/***
	 * For each color given, the generator will instance a Tile by 
	 * calling the OpenGL commands used on its construction + its color
	 * 
	 * @return Tileset OpenGL ID list
	 */
	unsigned int size = colors->size();
	for (unsigned int i = 0; i < size; i++){
		generic->compile(&(*colors)[i]);
		}
	}
	