/***
 * @file Ant.cpp
 * Ant implementation
 */
// Copyright 2019 by Julio Albornoz <gatalegath@protonmail.com>
// The License.txt file describes the conditions under which this software may be distributed.

#include "Ant.h"
#include <iostream>
Ant::Ant(int x, int y, int orientation, std::string rules, Tile* temp){
	/***
	* Ant Class, it has a position and an orientation, the ant will move depending 
	* on the instruction that the current tile color represents
	* 	
	* @param x, y: Ant Initial position
	* @param dir: Initial orientation of the ant
	* @param rules: Set of instructions that this particular ant follows
	* @param tile: Type of tile used on the current session
	*/	
	tile = temp;
	dir = orientation;
	pos = glm::ivec2(x, y);
	ruleset = rules;
	}
	
void Ant::command(int index){
	/*** 
	* Rotates ant and moves forward
	* 
	* @param index: Index of the current instruction being porcessed
	*/ 
	int size = tile->offset.size();
	dir = (((dir + tile->offset[ruleset[index]]) % size) + size) % size;
	pos += tile->directions[dir];
	}