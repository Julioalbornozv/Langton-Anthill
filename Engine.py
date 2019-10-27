import pygame
import numpy as np
import os

from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLU import *
from win32api import GetSystemMetrics

class Engine(object):
	"""
	Class concerning simulation rendering and user interaction
	"""
	def __init__(self, config):
		"""
		Creates OpenGL display and sets basic elements
		
		@param config:	Config object with the starting parameters
		
		@field tile_size: Size of the tile in pixels
		@field width: Window's width
		@field height: Window's height
		"""
		self.tile_size = config.getint('Display', 'CELL_SIZE')
		
		### Detects if fullscreen for an axis is active
		conf_width = config.getint('Display','WIDTH')
		conf_height = config.getint('Display','HEIGHT')
		
		if conf_width == -1:
			config['Display']['WIDTH'] = str(GetSystemMetrics(0)//self.tile_size)
		
		if conf_height == -1:
			config['Display']['HEIGHT'] = str(GetSystemMetrics(1)//self.tile_size)
			
		if conf_width == -1 and conf_height == -1:
			os.environ['SDL_VIDEO_WINDOW_POS'] = '0,0'
			
		### Screen size
		self.width = int(config.getint('Display','WIDTH') * self.tile_size)
		self.height = int(config.getint('Display','HEIGHT') * self.tile_size)
		
		### OpenGL screen initialization
		pygame.init()
		pygame.display.set_mode((self.width, self.height), OPENGL| DOUBLEBUF)
		pygame.display.set_caption("Langton's Ant")
		
		glViewport(0, 0, self.width, self.height)
		glMatrixMode(GL_PROJECTION)
		glLoadIdentity()
		gluOrtho2D(0.0, self.width, 0.0, self.height)
		glMatrixMode(GL_MODELVIEW)
		glLoadIdentity()
	
		glClearColor(0.0, 0.0, 0.0, 0.0)	
		glShadeModel(GL_SMOOTH)
		glClearDepth(1.0)
	
	def run(self, Anthill, TileGen):
		"""
		Rendering loop
		"""
		Map = dict({(0,0) : 0})	#Dictionary mapping the board  (Coord tuple : Tile_ID)
		ppf = 50	#Iterations per frame
		tiles = TileGen.generate_tiles()
		
		#TODO: Make angles configurable
		angles = dict({"L": -np.pi/2, "R": np.pi/2, "U": 0, "D": np.pi})

		run = True
		while(run):	
			### User Interaction
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
			
			self.render_tiles(Map)
			
			for iter in range(ppf):
				for ant in Anthill.ants:		#1 turn for each ant
					
					color = Map.get(tuple(ant.pos))
					if color == None:	#New tile is rendered
						color = 0
					
					Map.update({tuple(ant.pos) : (color+1) % (len(tiles)+1)}) 
					
					ant.command(angles.get(ant.ruleset[color]))  #Move ant based on recovered rule
								
					ant.pos[0] %= self.width	#Wraps ant position
					ant.pos[1] %= self.height
				
			pygame.display.flip()
		
	
	def render_tiles(self, map):
		"""
		Paint tiles of the current frame
		
		@param map: Dict((x,y) : ID), Dictionary which contain the position of the tiles and their respective color
		"""
		
		for coord in map.keys():
			hue = map.get(coord)
			if hue != 0:
				glPushMatrix()
				glTranslate(coord[0],coord[1],0)
				glCallList(hue)
				glPopMatrix()
				
	
		