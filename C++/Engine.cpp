/***
 * @file Engine.cpp
 * OpenGL Window and rendering execution
 */
// Copyright 2019 by Julio Albornoz <gatalegath@protonmail.com>
// The License.txt file describes the conditions under which this software may be distributed.

#include Engine.h

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
	int conf_width = config->width;
	int conf_height = config->height;
	
	if conf_width == 0{
		config->width = GetSystemMetrics(0)/tile->X;
		}
		
	if conf_height == 0{
		config->height = GetSystemMetrics(1)/tile->Y;
		}
	
	this->width = config->width;
	this->height = config->height;
	
	// Window Initialization
	GLFWwindow* window;
	
	if(!gldwInit()){
		return -1;
		}
		
	window = glfwCreateWindow(this->width, this->height, "Lanthill", NULL, NULL);
	if (!window){
        glfwTerminate();
        return -1;
		}
	glfwMakeContextCurrent(window);
	
	//OpenGL initial settings
	glViewport(0, 0, this->width, this->height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, this->width, 0.0, this->height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0);
	}
	
void Engine::run(Colony* Anthill, Color_Generator* ColorGen, Tile_Generator* TileGen){
	// Runs simulation
	int* TileIDs = TileGen.construct(ColorGen.palette);
	
	std::map<int[2],int>Map;
	Map[{0,0}] = 0;
	
	int speed = 50;
	int pre_speed = 0;
	
	while (!glfwWindowShouldClose(window)){
		
		//Move all user input to its own function, Refactor
		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
			glfwSetWindowShouldCLose(window, true);
			}
	
		//Speed Management
		else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && speed < 100){
			speed += 10;
			}
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && speed >= 10){
			speed -= 10;
			}
		
		else if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS){ //Refactor this block
			if (pre_speed == 0){
				pre_speed = speed;
				speed = 0;
				}
			else{
				speed = pre_speed;
				pre_speed = 0;
				}
			}
		
		//Shuffles current color palette
		/* [This blocks wont work until you find a way to shuffle the color palette (no np.shuffle)
		else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
			np.random.shuffle(ColorGen.palette)
			tile_IDs = TileGen.reset(ColorGen.palette)
			}
		#Generates new colorset
		elif event.key == K_g:
			delete Colorgen->palette
			ColorGen.random_palette(ColorGen.base)
			ColorGen.generate_colors()
			tile_IDs = TileGen.reset(ColorGen.palette)
		*/
        glClear(GL_COLOR_BUFFER_BIT);
		
		this->render(&Map);
		
		for (int iter = 0; iter < speed ; iter++){
			for (Ant &Anthill->ants : ant){
				int color;
				if (Map.count(ant.pos) == 0){
					color = 0
					}
				else{
					color = Map[ant.pos];
					}
				Map[ant.pos] = (color+1) % (TileIDs.size()+1);
				ant->command(color);
				
				ant->pos[0] %= this->width;
				ant->pos[1] %= this->height;
				}
			}
        glfwSwapBuffers(window);
        glfwPollEvents();
		}
		
	if (ColorGen->save){	//Move this to ColorGen destructor
		ColorGen->save();
		}
	
	glfwTerminate();
    return 0;
	}
	

void Engine::render_tiles(std::map<int[2], int>* map){
	/***
	* Paint tiles for the current frame
	*
	* @param map: Dict((x,y) : ID), Dictionary which contain the position of 
	* the tiles and their respective color
	*/
	
	for (auto it = map.begin(); it != map.end()){
		if (it->second != 0){
			glPushMatrix();
			glTranslate(it->first[0], it->second[0],0);
			glCallList(it->second);
			glPopMatrix();
			}
		}
	}