/***
 * @file Engine.cpp
 * OpenGL Window and rendering execution
 */
// Copyright 2019 by Julio Albornoz <gatalegath@protonmail.com>
// The License.txt file describes the conditions under which this software may be distributed.

#include "Engine.h"
#include <GL/glu.h>
#include <algorithm>

Engine::Engine(Config* config, Tile* tile){
	/***
	* Creates OpenGL display and sets basic elements
	* 
	* @param config:	Config object with the starting parameters
	* @param template: A generic tile created by a Tile Generator object
	* 
	* @field width: Window's width
	* @field height: Window's height
	* """
	*/
	// Window Initialization
	
	if(!glfwInit()){
		return;
		}
	
	GLFWmonitor* monitor = NULL;
	
	if (config->fullscreen){
		config->DWidth = GetSystemMetrics(0)/tile->X;
		config->DHeight = GetSystemMetrics(1)/tile->Y;
		monitor = glfwGetPrimaryMonitor();
		}
	
	width = config->DWidth * tile->X;
	height = config->DHeight * tile->Y;
	
	window = glfwCreateWindow(width, height, "Lanthill", monitor, NULL);
	
	if (!window){
        glfwTerminate();
        return;
		}
	glfwMakeContextCurrent(window);
	
	//OpenGL initial settings
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, width, 0.0, height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0);
	}
	
void Engine::run(Colony* Anthill, Color_Generator* ColorGen, Tile_Generator* TileGen){
	
	TileGen->construct(ColorGen->palette);	//Compile OpenGL lists
	
	std::map<std::pair<int,int>,int> Map;
	Map[std::make_pair(0,0)] = 0;
	
	int vel[2] = {50,0};
	speed = vel;
	
	//Start rendering
	while (!glfwWindowShouldClose(window)){
		
		catchInput(ColorGen, TileGen);

        glClear(GL_COLOR_BUFFER_BIT);
		
		render_tiles(&Map);
		
		for (int iter = 0; iter < *speed ; iter++){
			for (auto &ant : *Anthill->ants){
				int color;
				std::pair<int, int> coord = std::make_pair(ant.pos[0], ant.pos[1]);
				if (Map.count(coord) == 0){
					color = 0;
					}
				else{
					color = Map[coord];
					}
				
				Map[coord] = (color+1) % (ColorGen->size);
				ant.command(color);
				
				ant.pos[0] = ((ant.pos[0] % width) + width) % width;
				ant.pos[1] = ((ant.pos[1] % height) + height) % height;
				}
			}
        glfwSwapBuffers(window);
        glfwPollEvents();
		}
		
	if (ColorGen->write){	//Move this to ColorGen destructor
		ColorGen->save();
		}
	
	glfwTerminate();
	}
	
void Engine::catchInput(Color_Generator* ColorGen, Tile_Generator* TileGen){
	
	//Exit
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);
		}
	
	//Speed Management
	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && *speed < 100){
		*speed += 10;
		}
		
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && *speed > 10){
		*speed -= 10;
		}
	
	else if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS){ //Refactor this block
		(*speed == 0) ? speed-- : speed++;
		}
	
	//Shuffles current color palette
	else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
		std::random_shuffle(ColorGen->palette->begin(), ColorGen->palette->end());
		TileGen->reset(ColorGen->palette);
		}
	
	//Generates new colorset
	else if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS){
		delete ColorGen->palette;
		ColorGen->random_palette(ColorGen->base);
		ColorGen->generate_colors();
		TileGen->reset(ColorGen->palette);
		}
	}

void Engine::render_tiles(std::map<std::pair<int,int>, int>* map){
	/***
	* Paint tiles for the current frame
	*
	* @param map: Dict((x,y) : ID), Dictionary which contain the position of 
	* the tiles and their respective color
	*/
	
	for (auto it = map->begin(); it != map->end(); it++){
		if (it->second != 0){
			glPushMatrix();
			glTranslatef(std::get<0>(it->first), std::get<1>(it->first),0);
			glCallList(it->second);
			glPopMatrix();
			}
		}
	}