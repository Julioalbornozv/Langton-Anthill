from abc import ABC, abstractmethod
import numpy as np
from OpenGL.GL import *
from OpenGL.GLU import *
	
import pdb
class Tile(ABC):
	"""
	Class containing the information of a tile inside the grid.
	"""
	def __init__(self, size):
		self.size = size
	
	@property
	@abstractmethod
	def directions(self):
		"""
		Dictionary containing the translation vectors for the ant movement for each valid direction
		"""
		pass
		
	@property
	@abstractmethod
	def angles(self):
		"""
		Dictionary containing rotation angles for each instruction.
		"""
		pass
	
	@abstractmethod
	def compile(self, color):
		"""
		OpenGL Display List used to describe the tile
		
		@param color: Color associated with this tile
		"""
		pass
		
	
class Square_Tile(Tile):
	def __init__(self, config):
		super().__init__(config)
	
	@property
	def directions(self):
		return dict({0: (0,self.size), 1: (self.size,0), 2: (0,-self.size), 3: (-self.size,0)})
		
	@property
	def angles(self):
		return dict({"L": -np.pi/2, "R": np.pi/2, "U": 0, "D": np.pi})
		
	def compile(self, color):
		#pdb.set_trace()
		tile_ID = glGenLists(1)
		k = self.size/2
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