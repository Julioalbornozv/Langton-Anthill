/***
 * @file Monitor.h
 * Monitor Class implementation
 */
 
 #include "Monitor.h"
 #include <winuser.h>
 
 Monitor::Monitor(Config* param, int TileX, int TileY){
	full = param->fullscreen;
	
	if (full){
		param->DWidth = GetSystemMetrics(0)/TileX;	//TODO: This should be handled by a Config class setter
		param->DHeight = GetSystemMetrics(1)/TileY;
		}
	
	Width = param->DWidth * TileX;
	Height = param->DHeight * TileY;
	}
	
GLFWwindow* Monitor::GLFW_init(){
	/***
	 * Initializes the GLFW context, returns a pointer to the newly created  
     * GLFWwindow object
	 */
	if(!glfwInit()){
		return NULL;	//TODO: Throw error
		}
	
	GLFWmonitor* monitor = NULL;
	if (full){
		monitor = glfwGetPrimaryMonitor();
		}
		
	window = glfwCreateWindow(Width, Height, "Lanthill", monitor, NULL);
	
	if (!window){
        glfwTerminate();
        return NULL; //TODO: Throw error
		}
	
	glfwMakeContextCurrent(window);
	return window;
	}

void Monitor::OpenGL_init(){
    /***
     * Sets up initial OpenGL parameters
     */
	  
	glViewport(0, 0, Width, Height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, Width, 0.0, Height, -50.0, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0);
	}

int Monitor::getScreenWidth(){
	return Width;
	}
	
int Monitor::getScreenHeight(){
	return Height;
	}
	