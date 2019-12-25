/***
 * @file Monitor.h
 * Monitor Class, plataform dependant
 */
 
#include <GLFW/glfw3.h>
#include "Parameters.h"
/***
* Possible extension:
* Create an abstract class monitor, which has an abstract constructor and GLFW 
* initialization method, keep the same OpenGL init for both Windows and Linux 
* implementation of said class
*/

class Monitor{
public:
	Monitor(Config* param, int TileX, int TileY);
	
	int getScreenWidth();
	int getScreenHeight();
	GLFWwindow* GLFW_init();
	void OpenGL_init();
	
private:
	GLFWwindow* window;
	int Width, Height;
	bool full;
	};