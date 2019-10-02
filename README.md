# Langton Anthill

Real-Time implementation of the Langton's Ant Cellular Automata in python 3.7 [Wikipedia](https://en.wikipedia.org/wiki/Langton%27s_ant)

# Current Status
This project is able to simulate a color extended version of the celular automata, 
by changing the parameters located in the file "Parameters_Ant.txt" its possible to customise the number and position of the ants, ruleset used and screen dimensions.

The project is still a work in progress.

# Usage
Available settings are listed below:	(All settings are separated with tabs)
    WIDTH: Number of tiles on the x axis, writing -1 will use a number of tiles equivalent to the screen width
	HEIGHT: Similar to width but for the y axis, setting both on -1 starts a fullsreen window
	CELL SIZE: Size of the grid in pixels
	RULESET: Three options are available
	         - A sequence of instructions 
			   (Ex: LRRLRLRLRL)
			 - KN followed by a number will generate a random ruleset with a specific  size 
			   (Ex: KN7 => LRLRRLR)
			 - Using KE instead of KN generates a ruleset which includes a 0° and 180°  rotation instructions (U and D)
			   (Ex: KE8 => LRURULDD
	COLOR: Currently its only option is Random
	
	Finally, the following lines consist of multiple strings representing the ants starting tile and orientation (N = 0, E = 1, S = 2, W = 3).
	
	ANT	30	40	0	will create an ant on the position (30, 40) of the grid while facing north

To run the simulation with the given parameters
    python "Langton's Ant.py"

Press Esc to quit the simulation, pressing the w and s keys will adjust the number of iterations simulated per frame. Simulation can be freezed by reducing the speed to its minimum value.

# Dependencies
The program currently uses the following libraries: 
numpy, pygame, OpenGL.GL, OpenGL.GLU and win32api

# TODO
* Unit Tests
* Code Refactoring
* Better Color support
* Simplify Parameter input
* Improve Performance