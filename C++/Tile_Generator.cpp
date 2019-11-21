/***
 * @file Tile_Generator.cpp
 * Tile factory
 */
// Copyright 2019 by Julio Albornoz <gatalegath@protonmail.com>
// The License.txt file describes the conditions under which this
// software may be distributed.

#include "Generators.h"
#include "Tile.h"

Tile_Generator::Tile_Generator(Config* config){
	this->scale = config->scale;
	this->shape = config->shape;
	
	this->generic = this->form();
	}
	
Tile* Tile_Generator::form(){
	/***
	 * Initializes a Tile object, if the shape requested is not known it 
	 * will raise an error.
	 */
	if (this->shape.compare("SQUARE") == 0){
		return new Square_Tile(this->scale);
		}
	else if (this->shape.compare("HEXAGON") == 0){
		return new Hexagon_Tile(this->scale);
		}	
	else{
		throw std::invalid_argument("Unknown tile shape");
		}
	}
	
int* Tile_Generator::reset(std::vector<glm::vec3>* colors){
	/***
	 * Deletes previous Tile instances, creates a new set based on 
	 * the colors given.
	 * 
	 * @param colors: New colorset
	 * 
	 * @return New Tileset OpenGL ID list
	 */
	 glDeleteLists(1, colors->size());
	 
	 return construct(colors);
	}
	
int* Tile_Generator::construct(std::vector<glm::vec3>* colors){
	/***
	 * For each color given, the generator will instance a Tile by 
	 * calling the OpenGL commands used on its construction + its color
	 * 
	 * @return Tileset OpenGL ID list
	 */
	unsigned int size = colors->size();
	int* TileID = new int[size];
	for (unsigned int i = 0; i < size; i++){
		int id = generic->compile(&(*colors)[i]);
		TileID[i] = id;
		}
		
	return TileID;
	}