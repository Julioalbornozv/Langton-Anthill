/***
 * @file Tile.h
 * Tile abstract class
 */
// Copyright 2019 by Julio Albornoz <gatalegath@protonmail.com>
// The License.txt file describes the conditions under which this software may be distributed.

#pragma once
#include <unordered_map>
#include <string>

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>

class Tile{
	/***
	 * Class which contains the information required to construct a Tile of
	 * a specific shape. 
	 * 	
	 * @param scale: Scale used by the program
	 * @param X: Tile Width
	 * @param Y: Tile Height
	 * 	
	 * @field directions: Ant movement vectors asociated with the ant 
	 *                    current orientation
	 * @field offset: Result of rotating the ant after reading a specific rule
	 */
public:
	int scale, X, Y;
	std::unordered_map<int, glm::vec2> directions;
	std::unordered_map<char, int> offset;
	
	virtual int compile(glm::vec3 *color) = 0;
	};
	
class Square_Tile : public Tile{
public:
	Square_Tile(int scale);
	int compile(glm::vec3 *color);
	};
	
class Hexagon_Tile : public Tile{
public:
	Hexagon_Tile(int scale);
	int compile(glm::vec3 *color);
	};