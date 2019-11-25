/***
 * @file Camera.cpp
 * Camera Class implementation
 */

#include "Camera.h"

Camera::Camera(glm::vec3 Pv, glm::vec3 Tv, glm::vec3 Upv){
	Position = Pv;
	Target = Tv;
	Up = Upv;
	updateVectors();
	}
	
void Camera::move(CameraCom command){
	switch (command){
		case UP:
			Position[1] += SPEED;
			Target[1] += SPEED;
			break;
		case DOWN:
			Position[1] -= SPEED;
			Target[1] -= SPEED;
			break;
		case LEFT:
			Position[0] -= SPEED;
			Target[0] -= SPEED;
			break;
		case RIGHT:
			Position[0] += SPEED;
			Target[0] += SPEED;
			break;
		}
	}
	
void Camera::updateVectors(){
	//Replace this with glm LookAt after shaders are implemented
	glLoadIdentity();
	gluLookAt(Position[0], Position[1], Position[2],
				  Target[0], Target[1], Target[2],
				  Up[0], Up[1], Up[2]);
	
	//glm::lookAt(cameraPos, cameraTarget, cameraUp);	
	}