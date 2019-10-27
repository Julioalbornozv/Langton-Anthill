# coding=utf-8
import configparser as cfg
import numpy as np

import Tile_Gen as tg
import Ant as A
import Colony as col
import Engine as eng
			
# Read initial parameters
config = cfg.ConfigParser()
config.read('config.ini')

# Initialize engine
render = eng.Engine(config)

# Creates Ants
Anthill = col.Colony(config)
Anthill.load_ants("ants.txt")

# Creates colored Tiles
TGen = tg.Tile_Generator(config)

### Program Starts
render.run(Anthill, TGen)