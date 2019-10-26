# coding=utf-8

#TODO: Integrate logging library
import pygame
import configparser as cfg
import numpy as np
import os
import random
import time

from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLU import *
from win32api import GetSystemMetrics

import Tile_Gen as tg
import Ant as A
import Colony as col

import pdb
def init():
	"""
	Initializes OpenGL Display
	"""
	#TODO Migrate from pygame to cyglfw
	pygame.init()
	pygame.display.set_mode((ancho, alto), OPENGL| DOUBLEBUF)
	pygame.display.set_caption("Langton's Ant")
	
	glViewport(0, 0, ancho, alto)
	glMatrixMode(GL_PROJECTION)
	glLoadIdentity()
	gluOrtho2D(0.0, ancho, 0.0, alto)
	glMatrixMode(GL_MODELVIEW)
	glLoadIdentity()

	glClearColor(0.0, 0.0, 0.0, 0.0)	
	glShadeModel(GL_SMOOTH)
	glClearDepth(1.0)
	return

def Paint_path(map):
	"""
	Paint tiles from the current frame
	
	@param map: Dict((x,y) : ID), Dictionary which contain the position of the tiles and their respective color
	"""
	
	for coord in map.keys():
		hue = map.get(coord)
		if hue != 0:
			glPushMatrix()
			glTranslate(coord[0],coord[1],0)
			glCallList(hue)
			glPopMatrix()
			
#-------------------- Parameter Extraction --------------------#

#Read initial parameters
config = cfg.ConfigParser()
config.read('config.ini')

k = config.getint('Display', 'CELL_SIZE')

#Sets screen size when requested
#TODO: Standardize x,y coordinates (Remove as many divisions as possible)

if config.getint('Display','WIDTH') == -1 and config.getint('Display','HEIGHT') == -1:
	os.environ['SDL_VIDEO_WINDOW_POS'] = '0,0'
	
if config.getint('Display','WIDTH') == -1:
	config['Display']['WIDTH'] = str(GetSystemMetrics(0)//k)
	
if config.getint('Display','HEIGHT') == -1:
	config['Display']['HEIGHT'] = str(GetSystemMetrics(1)//k)
	
dim = config.getint('Display','WIDTH')
height = config.getint('Display','HEIGHT')


#Visual Display
ancho = int(dim*k)
alto = int(height*k)	

#-------------------- Program Logic ----------------------#
#---------------------------------------------------------#
init()
run = True

#-------------------- Ant Generation --------------------#

directions = dict({0: (0,k), 1: (k,0), 2: (0,-k), 3: (-k,0)})
angles = dict({"L": -np.pi/2, "R": np.pi/2, "U": 0, "D": np.pi})

Anthill = col.Colony(directions, config)
Anthill.load_ants("ants.txt")

#-------------------- Tile Generation --------------------#
Tgen = tg.Tile_Generator(config)
tiles = Tgen.generate_tiles()

#-------------------- Main Loop --------------------------#

Map = dict({(0,0) : 0})	#Dictionary mapping the board  (Coord tuple : Tile_ID)
ppf = 50	#Iterations per frame

while(run):	
	for event in pygame.event.get():
		if event.type == QUIT:
			run = False
	
		if event.type == KEYDOWN:
			if event.key == K_ESCAPE:
				run = False
			elif event.key == K_w:
				ppf += 10
				if ppf > 100:
					ppf = 100
			elif event.key == K_s:
				ppf -= 10
				if ppf < 0:
					ppf = 0
			
	glClear(GL_COLOR_BUFFER_BIT)
	
	Paint_path(Map)
	
	for iter in range(ppf):
		for ant in Anthill.ants:		#1 turn for each ant
			
			color = Map.get(tuple(ant.pos))
			if color == None:	#New tile is rendered
				color = 0
			
			Map.update({tuple(ant.pos) : (color+1) % (len(tiles)+1)}) 
			
			ant.command(angles.get(ant.ruleset[color]))  #Move ant based on recovered rule
						
			ant.pos[0] %= ancho	#Wraps ant position
			ant.pos[1] %= alto
		
	pygame.display.flip()
	#pygame.time.wait(int(1000/60)) #FPS
		