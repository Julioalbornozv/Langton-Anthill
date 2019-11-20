/***
 * @file Ant.h
 * Ant Class
 */
// Copyright 2019 by Julio Albornoz <gatalegath@protonmail.com>
// The License.txt file describes the conditions under which this software may be distributed.

#pragma once
#include "Tile.h"
#include <glm/glm.hpp>
#include <string>

class Ant{
public:
	Tile* tile;
	int dir;
	glm::vec2 pos;
	std::string ruleset;
	
	Ant(int x, int y, int dir, std::string rules, Tile* tile);
	void command(int index);
	}