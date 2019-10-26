

![""](https://raw.githubusercontent.com/Julioalbornozv/Langton-Anthill/master/examples/Ex1/Example_1.png)

# Langton's Anthill

Real-Time implementation of the Langton's Ant Cellular Automata in python 3.7 [Wikipedia](https://en.wikipedia.org/wiki/Langton%27s_ant)

# Usage
To run the program execute:

    python "Langton's Ant.py"

Press Esc to quit the simulation, pressing the w and s  keys will adjust the number of iterations simulated per frame. The simulation can be stopped temporarily by reducing the speed to its minimum value.

# Customization
By default the program simulates the RL ruleset (Simple Langton ant), modifying the simulation is accomplished by changing any of the following configuration files.

## config.ini
Initialization settings of the program, seprated in three sections:
### Display Section
* `WIDTH` & `HEIGHT`: Size of the grid which will be displayed, where each contains the number of tiles for the x and y axis. Placing `-1` on this fields will match the display with the screen size (Fullscreen if both).
* `CELL_SIZE`: Size of each tile in pixels

### Color Section
* `SCHEME`: Two possible settings, `LOAD` will read the colors found in "colors.txt" while `RANDOM`generates a new colorset with random colors.
* `INTERPOLATION`: Toggles color interpolation on a specific colorspace, interpolation is used to generate a colorset for a big ruleset without specifying each color individually. Available options are `RGB` interpolation and `NONE`  which will use the same colors repeatedly instead of generating new colors. 
* `SHUFFLE`: If is set to `YES`it will scramble the colors of the colorset after being generated.
* `SAVE`: If set to `YES` it will write a backup of the colors used in this session.

### Ruleset Section
* `LENGTH`: Number of instructions the ruleset will use
* `SYMBOLS`: A string where each character represents an instruction
* `DEFAULT`: Ruleset which is used by all ants by default, if set to `RANDOM` it will generate a string of size `LENGTH` using the symbols given beforehand.

## ants.txt: 
TSV file where each row contains the data of a single ant, the format is as follows:

    X	Y	Orientation	Ruleset*

* `X` & `Y`: Starting tile of the ant.
* `Orientation`: Number representing which direction the ant faces. (Current options: {0: North, 1:East, 2:South, 3:West})
* `Ruleset`: Optional column, placing a ruleset here will override the default ruleset for the ant, ommiting this column will make the ant follow the default ruleset.

The first three settings can be randomized by writing `R`, in the case of the Ruleset writing `RANDOM` will generate a ruleset with the same length as the default ruleset given.

## color.txt
TSV file where each row contains the RGB representation of a color, with one column for each color channel.

# External Libraries 
- numpy
- pygame 
- OpenGL.GL
- OpenGL.GLU
- win32
- configparser

# TODO
* Unit Tests
* Code Refactoring
* Improve Performance
