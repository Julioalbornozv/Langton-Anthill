import pygame
import numpy as np
import os

from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLU import *
from win32api import GetSystemMetrics

import pdb
class Engine(object):
	"""
	Class concerning simulation rendering and user interaction
	"""
	def __init__(self, config, template):
		"""
		Creates OpenGL display and sets basic elements
		
		@param config:	Config object with the starting parameters
		@param template: A generic tile created by a Tile Generator object
		
		@field width: Window's width
		@field height: Window's height
		"""
		
		### Detects if fullscreen for an axis is active
		conf_width = config.getint('Display','WIDTH')
		conf_height = config.getint('Display','HEIGHT')
		
		if conf_width == -1:
			config['Display']['WIDTH'] = str(GetSystemMetrics(0)//template.x)
			
		if conf_height == -1:
			config['Display']['HEIGHT'] = str(GetSystemMetrics(1)//template.y)
			
		os.environ['SDL_VIDEO_WINDOW_POS'] = '0,0'
			
		### Screen size
		self.width = int(config.getint('Display','WIDTH') * template.x)
		self.height = int(config.getint('Display','HEIGHT') * template.y)
		
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
	
	def run(self, Anthill, ColorGen, TileGen):
		"""
		Runs simulation
		"""
		tile_IDs = TileGen.construct(ColorGen.palette)
		Map = dict({(0,0) : 0})	#Dictionary mapping the board  (Coord tuple : Tile_ID)
		
		speed = 50	#Iterations per frame
		pre_speed = 0
		
		run = True
		while(run):	
			### User Interaction
			for event in pygame.event.get():
				if event.type == QUIT:
					run = False
			
				if event.type == KEYDOWN:
					if event.key == K_ESCAPE:
						if ColorGen.write:
							ColorGen.save()		#Saves last palette
						run = False
					
					#Speed management
					elif event.key == K_w and speed <= 100:
						speed += 10
					elif event.key == K_s and speed >= 10:
						speed -= 10
						
					#Pause
					elif event.key == K_p:
						if pre_speed == 0:
							pre_speed = speed
							speed = 0
						else:
							speed = pre_speed
							pre_speed = 0
					
					#Shuffles current color palette
					elif event.key == K_r:
						np.random.shuffle(ColorGen.palette)
						tile_IDs = TileGen.reset(ColorGen.palette)
					
					#Generates new colorset
					elif event.key == K_g:
						ColorGen.random_palette(ColorGen.base)
						ColorGen.generate_colors()
						tile_IDs = TileGen.reset(ColorGen.palette)
						
			glClear(GL_COLOR_BUFFER_BIT)
			
			self.render_tiles(Map)
			
			for iter in range(speed):
				for ant in Anthill.ants:		#1 turn for each ant
					
					color = Map.get(tuple(ant.pos))
					if color == None:	#New tile is rendered
						color = 0
					
					Map.update({tuple(ant.pos) : (color+1) % (len(tile_IDs)+1)}) 
					
					ant.command(color)  #Move ant based on recovered rule
					
					ant.pos[0] %= self.width	#Wraps ant position
					ant.pos[1] %= self.height
				
			pygame.display.flip()
			
	def render_tiles(self, map):
		"""
		Paint tiles for the current frame
		
		@param map: Dict((x,y) : ID), Dictionary which contain the position of the tiles and their respective color
		"""
		
		for coord in map.keys():
			hue = map.get(coord)
			if hue != 0:
				glPushMatrix()
				glTranslate(coord[0],coord[1],0)
				glCallList(hue)
				glPopMatrix()
				
	
		