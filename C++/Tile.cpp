/***
 * @file Tile.cpp
 * Tile type implementations
 */
// Copyright 2019 by Julio Albornoz <gatalegath@protonmail.com>
// The License.txt file describes the conditions under which this software may be distributed.

#include "Tile.h"
#include <math.h>

#define PI 3.141592653589793

Square_Tile::Square_Tile(int scale){
	int R = scale;
	this->scale = R;
	X = R;
	Y = R;
	
	directions = {{0, glm::vec2(0.0, R)}, 
	              {1, glm::vec2(R,0.0)},
				  {2, glm::vec2(0.0, -R)}, 
				  {3,glm::vec2(-R, 0.0)}};
	
	offset = {{'R', 1}, {'L', -1}, {'U', 0}, {'D', 2}};
	}
	
void Square_Tile::compile(glm::vec3* color){
	int TileID = glGenLists(1);
	float k = (float)scale / 2.0f;
	glm::vec3 n_col = *color / 255.0f;		//Color Normalization
	
	float* p_col = glm::value_ptr(n_col);	//Cast to float array
	
	//------------------------------------
	glNewList(TileID, GL_COMPILE);
	glPushMatrix();
	
	glBegin(GL_QUADS);
	glColor3fv(p_col);
	glVertex2f(-k, -k);
	glVertex2f(-k, k);
	glVertex2f(k, k);
	glVertex2f(k, -k);
	glEnd();
	
	glPopMatrix();
	glEndList();
	
	}
	
Hexagon_Tile::Hexagon_Tile(int scale){
	this->scale = scale;
	float R = (float)this->scale / 2.0f;
	int r = (int)(R * cos(PI / 6.0f));
	int d = (int)(3.0f*R/2.0f);
	X = 2*d;
	Y = 2*r;
	
	directions = {{0, glm::vec2(0.0f, 2*r)}, 
				  {1, glm::vec2(d,r)}, 
				  {2, glm::vec2(d, -r)},
				  {3, glm::vec2(0.0f, -2*r)}, 
				  {4, glm::vec2(-d,-r)}, 
				  {5, glm::vec2(-d, r)}};
				  
	offset = {{'R', 1}, {'S',2}, {'L',-1}, {'M',-2}, {'T',0}, {'B',3}};
	}

void Hexagon_Tile::compile(glm::vec3 *color){
	int TileID = glGenLists(1);
	float R = (float)(scale / 2.0f);
	
	glm::vec3 n_col = *color / 255.0f;
	
	float* p_col = glm::value_ptr(n_col);	//Cast to float array
	
	//------------------------------------
	glNewList(TileID,GL_COMPILE);
	glPushMatrix();
	
	glBegin(GL_POLYGON);
	glColor3fv(p_col);
	for (int i = 0; i < 6; i++){
		glVertex2f(R * cos(i*PI/3.0f), R * sin(i*PI/3.0f));
		}	
	glEnd();
	
	glPopMatrix();
	glEndList();
	
	}
	
	
	
	
	