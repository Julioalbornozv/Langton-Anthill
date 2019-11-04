# coding=utf-8
import configparser as cfg
import numpy as np

import Tile_Gen as Tg
import Color_Gen as Cg
import Ant as A
import Colony as Col
import Engine as Eng

### Main procedure
			
# Read initial parameters
config = cfg.ConfigParser()
config.read('config.ini')

# Initialize tiles
TGen = Tg.Tile_Generator(config)

# Initialize engine
render = Eng.Engine(config, TGen)

# Creates Ants
Anthill = Col.Colony(config, TGen.template)
Anthill.load_ants("ants.txt")

# Creates colored Tiles
CGen = Cg.Color_Generator(config)

### Program Starts
render.run(Anthill, CGen)