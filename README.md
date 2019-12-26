# Langton Anthill

## Description
Langton Anthill is a C++ implementation of the [Langton's Ant](https://en.wikipedia.org/wiki/Langton%27s_ant) Ant cellular automata for Windows, the project is highly customizable, supporting different extensions of the automata (number of ants, rulesets and hexagonal grids). The project is still a work in progress so features may vary with time.

## Screenshots
![""](https://raw.githubusercontent.com/Julioalbornozv/Langton-Anthill/master/examples/Ex1/Example_1.png)

![""](https://raw.githubusercontent.com/Julioalbornozv/Langton-Anthill/master/examples/Ex4/Example_4.png)

# Installation

Download the source code of this project and run `make install` to build the program

# Usage
During execution the following instructions are available
* `Esc`:    Exit window
* `Up/Down Arrow Keys`:  Increase/Decrease speed of execution
* `w/a/s/d`: Control Camera movement
* `p`:  Pause/Resume the execution.
* `g`:  Generates a new set of colors
* `r`:  Shuffles the current set of colors

# Customization
By default the program simulates the RL ruleset (Simple Langton ant), modifying the simulation is accomplished by changing any of the configuration files shown below. 

Some examples can be found in the example folder, to reproduce them, copy the configuration files located in the example folder and place them on the executable location.

## config.ini
Initialization settings of the program, separated in four sections:

### Display
* `FULLSCREEN`: `YES` by default, if set to `NO` the display will initialize as a window with a specific size
* `WIDTH` & `HEIGHT`: Set the window size when fullscreen is disabled

### Grid
* `ADJUST`: If this value is enabled, the grid used by the program will have the same size as the display.
* `WIDTH` & `HEIGHT`: Sets the grid dimensions, measured in tiles.

### Color
* `BASE`: Number of colors used to generate color sets.
* `SCHEME`: Two possible settings, `LOAD` will read the colors found in "colors.txt" while `RANDOM`generates a new colorset with random colors.
* `INTERPOLATION`: Toggles color interpolation, this is used to generate a colorset for a long ruleset without specifying each color individually. Available options are `RGB` interpolation and `NONE`  which will use the same colors repeatedly instead of generating new colors. 
* `SHUFFLE`: If set to `YES`,it will scramble the colors of the colorset after being generated.
* `SAVE`: If set to `YES`, it will save the colors used in the current session on a txt file.

### Ruleset
* `LENGTH`: Number of instructions the ruleset will use
* `SYMBOLS`: A string with the allowed instructions by the program. Allows the user to restrict a ruleset to a specific subset of instrucions
* `DEFAULT`: Ruleset which is used by all ants by default, if set to `RANDOM` it will generate a string of size `LENGTH` using the symbols given in `SYMBOLS`.
* `SAVE`: If set to `YES` it will save a backup of the ants used in this session.

### Tile
* `SHAPE`: Shapes of the tiles, options are "SQUARE" and "HEXAGON". Square tiles have four instructions available (R = 90°, L = -90°, U = 0°, D = 180°) while an hexagonal tile can choose between six (R = 60°, S = 120°. L = -60°, M = -120°, U = 0°, D = 180°)
* `SCALE`: Scale factor used by the program to determine the tile dimensions

## ants.txt: 
Text file with tab separated values, where each row contains the data of a single ant, the format is as follows:

    X	Y	Orientation	Ruleset*

* `X` & `Y`: Starting tile of the ant.
* `Orientation`: Number representing which direction the ant faces. (For square tiling: {0: North, 1:East, 2:South, 3:West}, for hexagonal tiling options are: {0: North, 1:Northeast, 2:Southeast, 3:South, 4:Southwest, 5: Northwest})
* `Ruleset`: Optional column, placing a ruleset here will override the default ruleset for that specific ant.

The first three settings can be randomized by writing `R`, in the case of the Ruleset writing `RANDOM` will generate a ruleset with the same length as the default ruleset given.

## color.txt
Text file with tab separated values, where each row contains the RGB representation of a color, with one column for each color channel.

# Dependencies
- OpenGL
- GLFW
- GLM
