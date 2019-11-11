from abc import ABC, abstractmethod
import numpy as np
from OpenGL.GL import *
from OpenGL.GLU import *

class Tile(ABC):
	def __init__(self, scale):
		"""
		Class which contains the information required to construct a Tile of a specific shape. 
		
		@param scale: Scale used by the program
		@param x: Tile Width
		@param y: Tile Height
		
		@field directions: Ant movement vectors asociated with the ant current orientation
		@field offset: Result of rotating the ant after reading a specific rule
		"""
		self.scale = scale
	
	@property
	@abstractmethod
	def directions(self):
		"""
		Dictionary containing the movement of an ant for each valid direction
		
				new_pos = current_pos + vector
		"""
		pass
		
	@property
	@abstractmethod	
	def offset(self):
		"""
		Dictionary containing an integer for each instruction, which is used to
		obtain the next orientation
		
				next_dir = (current_dir + offset) % max (max = number of keys)
		"""
		pass
		
	@abstractmethod
	def compile(self, color):
		"""
		OpenGL Display List used to draw the tile
		
		@param color: Color associated with this tile
		"""
		pass
		
	
class Square_Tile(Tile):
	def __init__(self, config):
		super().__init__(config)
		self.x = self.scale
		self.y = self.scale
	
	@property
	def directions(self):
		R = self.scale
		return dict({0: (0,R), 1: (R,0), 2: (0,-R), 3: (-R,0)})
		
	@property
	def offset(self):
		"""
		Rotations: R = 90°, L = -90°, U = 0°, D = 180°
		"""
		return dict({"R": 1, "L": -1, "U": 0, "D": 2})
		
	def compile(self, color):
		tile_ID = glGenLists(1)
		k = self.scale/2
		n_color = color / 255.0		#Normalizes color
		
		glNewList(tile_ID,GL_COMPILE)
		glPushMatrix()
		
		glBegin(GL_QUADS)
		glColor3fv(n_color)
		glVertex2fv([-k, -k])
		glVertex2fv([-k, k])
		glVertex2fv([k, k])
		glVertex2fv([k, -k])
		glEnd()
		
		glPopMatrix()
		glEndList()
		
		return tile_ID
		
class Hexagonal_Tile(Tile):
	def __init__(self, config):
		super().__init__(config)
		R = self.scale / 2
		r = int(R * np.cos(np.pi/6))
		d = int(3*R/2)
		self.x = 2*d
		self.y = 2*r
		
	@property
	def directions(self):
		R = self.scale / 2				#Maximal Radius	
		r = int(R * np.cos(np.pi/6))	#Minimal Radius
		d = int(3*R/2)					#Distance between centers for diagonal movements
		
		return dict({0: (0,2*r), 1: (d,r), 2: (d,-r), 3: (0,-2*r), 4: (-d,-r), 5: (-d,r)})
		
	@property
	def offset(self):
		"""
		Rotations: R = 60°, S = 120°. L = -60°, M = -120°, U = 0°, D = 180°
		"""
		return dict({"R": 1, "S": 2, "L": -1, "M": -2, "T": 0, "B": 3})
		
	def compile(self, color):
		tile_ID = glGenLists(1)
		R = self.scale / 2
		
		n_color = color / 255.0		#Normalizes color
		
		glNewList(tile_ID,GL_COMPILE)
		glPushMatrix()
		
		glBegin(GL_POLYGON)
		glColor3fv(n_color)
		for i in range(6):
			glVertex2fv([R * np.cos(i*np.pi/3.0), R * np.sin(i*np.pi/3.0)])
		
		glEnd()
		
		glPopMatrix()
		glEndList()
		
		return tile_ID
