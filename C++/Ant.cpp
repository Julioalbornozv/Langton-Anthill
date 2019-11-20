/***
 * @file Ant.cpp
 * Ant implementation
 */
// Copyright 2019 by Julio Albornoz <gatalegath@protonmail.com>
// The License.txt file describes the conditions under which this software may be distributed.


Ant::Ant(int x, int y, int dir, std::string rules, Tile* tile){
	/***
	* Ant Class, it has a position and an orientation, the ant will move depending 
	* on the instruction that the current tile color represents
	* 	
	* @param x, y: Ant Initial position
	* @param dir: Initial orientation of the ant
	* @param rules: Set of instructions that this particular ant follows
	* @param tile: Type of tile used on the current session
	*/
	this->tile = tile;
	this->dir = dir;
	this->pos = glm::vec2(x, y);
	this->ruleset = rules;
	}
	
Ant::Ant(int index){
	/*** 
	* Rotates ant and moves forward
	* 
	* @param index: Index of the current instruction being porcessed
	*/ 
	this->dir = (this->dir + this->tile->offset[this->ruleset[index]]) % this->tile->offset.size();
	this->pos += this->directions[this->dir];
	}