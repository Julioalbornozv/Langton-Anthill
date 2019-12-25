/***
 * @file Engine.cpp
 * OpenGL Window and rendering execution
 */
// Copyright 2019 by Julio Albornoz <gatalegath@protonmail.com>
// The License.txt file describes the conditions under which this software may be distributed.

#include "Engine.h"
#include "Camera.h"
#include <algorithm>
#include <glm/glm.hpp>

Engine::Engine(Config* config, Tile* tile, Monitor* monitor){
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
	/** If windows:{...} else if Linux: {...} **/
	
	window = monitor->GLFW_init();
	
	//OpenGL settings:
	monitor->OpenGL_init();
	
	// Grid Initialization
	if (config->adjust){
		config->GWidth = monitor->getScreenWidth();	//TODO: Handle this through a Param setter
		config->GHeight = monitor->getScreenHeight();
		Gwidth = config->GWidth;
		Gheight = config->GHeight;
		}	
		
	else{
		Gwidth = config->GWidth * tile->X;
		Gheight = config->GHeight * tile->Y;
		}
	}
	
void Engine::run(Colony* Anthill, Color_Generator* ColorGen, Tile_Generator* TileGen){
	
	TileGen->construct(ColorGen->palette);	//Compile OpenGL lists
	
	std::map<std::pair<int,int>,int> Map; //Move this to a Grid class, including the constructor commands from above
	Map[std::make_pair(0,0)] = 0;
	
	int vel[2] = {50,0};
	speed = vel;
	
	Camera visor = Camera(glm::vec3(0.0f, 0.0f, 3.0f),
						   glm::vec3(0.0f, 0.0, 0.0f),
						   glm::vec3(0.0f, 1.0f, 0.0f));
	
	//Start rendering
	while (!glfwWindowShouldClose(window)){
		
		//Move this to own function
		
		catchInput(ColorGen, TileGen, &visor);
		
		visor.updateVectors();
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
				
				ant.pos[0] = ((ant.pos[0] % Gwidth) + Gwidth) % Gwidth;
				ant.pos[1] = ((ant.pos[1] % Gheight) + Gheight) % Gheight;
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
	
void Engine::catchInput(Color_Generator* ColorGen, Tile_Generator* TileGen, Camera* visor){
	//TODO: Improve this method
	
	//Exit
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);
		}
	
	//Speed Management
	else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && *speed < 100){
		*speed += 10;
		}
		
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && *speed > 10){
		*speed -= 10;
		}
	
	else if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS){
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
	
	//Camera movement
	else if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
		visor->move(UP);
		}
	
	else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		visor->move(DOWN);
		}	
	else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		visor->move(RIGHT);
		}
	else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
		visor->move(LEFT);
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