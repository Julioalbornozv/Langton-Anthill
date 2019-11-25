/***
 * @file Camera.h
 * Camera class, used to navigate grids bigger than the display
 */

#include <glm/vec3.hpp>
#include <GL/glu.h>

enum CameraCom{
		LEFT, RIGHT, UP, DOWN
		};

class Camera{
public:
	Camera(glm::vec3 Pv, glm::vec3 target, glm::vec3 Upv);
	void move(CameraCom command);
	void updateVectors();
	
private:
	glm::vec3 Position;
	glm::vec3 Target;
	glm::vec3 Up;
	float SPEED = 5.0;
	};