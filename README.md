

![""](https://raw.githubusercontent.com/Julioalbornozv/Langton-Anthill/master/examples/Ex1/Example_1.png)

# Langton's Anthill

Real-Time implementation of the [Langton's Ant](https://en.wikipedia.org/wiki/Langton%27s_ant) Cellular Automata for Windows

# Usage
To run the program execute:

    python "Langton's Ant.py"

During the execution the following instructions are available
* `Esc`:    Exit window
* `w`/`s`:  Increase/Decrease speed of execution
* `p`:  Pause/Resume the execution.
* `r`:  Shuffles the colors being used by the program
* `g`:  Generates a new set of colors

# Customization
By default the program simulates the RL ruleset (Simple Langton ant), modifying the simulation is accomplished by changing any of the configuration files shown below. 

Some examples can be found in the example folder, to reproduce them copy the configuration files from that example into the project root folder.

## config.ini
Initialization settings of the program, separated in four sections:

### Display
* `WIDTH` & `HEIGHT`: Size of the grid which will be displayed, where each contains the number of tiles for the x and y axis. Placing `-1` on this fields will match the display with the screen size (Fullscreen if both).

### Color
* `BASE`: Number of colors given to the program
* `SCHEME`: Two possible settings, `LOAD` will read the colors found in "colors.txt" while `RANDOM`generates a new colorset with random colors.
* `INTERPOLATION`: Toggles color interpolation, this is used to generate a colorset for a long ruleset without specifying each color individually. Available options are `RGB` interpolation and `NONE`  which will use the same colors repeatedly instead of generating new colors. 
* `SHUFFLE`: If is set to `YES`it will scramble the colors of the colorset after being generated.
* `SAVE`: If set to `YES` it will write a backup of the colors used in this session.

### Ruleset
* `LENGTH`: Number of instructions the ruleset will use
* `SYMBOLS`: A string with the instructions that will be used if the program generates rulesets of its own
* `DEFAULT`: Ruleset which is used by all ants by default, if set to `RANDOM` it will generate a string of size `LENGTH` using the symbols given in `SYMBOLS`.
* `SAVE`: If set to `YES` it will write a backup of the ants used in this session.

### Tile
* `SHAPE`: Shapes of the tiles, options are "SQUARE" and "HEXAGON". Square tiles have four instructions available (R = 90°, L = -90°, U = 0°, D = 180°) while an hexagon tile can choose between six (R = 60°, S = 120°. L = -60°, M = -120°, U = 0°, D = 180°)
* `SCALE`: Scale factor used by the program to determine the tile dimensions

## ants.txt: 
TSV file where each row contains the data of a single ant, the format is as follows:

    X	Y	Orientation	Ruleset*

* `X` & `Y`: Starting tile of the ant.
* `Orientation`: Number representing which direction the ant faces. (For square tiling: {0: North, 1:East, 2:South, 3:West}, for hexagonal tiling options are: {0: North, 1:Northeast, 2:Southeast, 3:South, 4:Southwest, 5: Northwest})
* `Ruleset`: Optional column, placing a ruleset here will override the default ruleset for that specific ant.

The first three settings can be randomized by writing `R`, in the case of the Ruleset writing `RANDOM` will generate a ruleset with the same length as the default ruleset given.

## color.txt
TSV file where each row contains the RGB representation of a color, with one column for each color channel.

# External Libraries 
- numpy
- pygame 
- PyOpenGL
- win32
- configparser
