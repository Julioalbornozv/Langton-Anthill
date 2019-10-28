import numpy as np
import Tile
from OpenGL.GL import *
from OpenGL.GLU import *

class Tile_Generator(object):
	def __init__(self, config):
		self.size = config.getint('Tile', 'SIZE')
		self.shape = config['Tile']['SHAPE']
		
		self.types = dict({"SQUARE": Tile.Square_Tile})
		
		self.template = self.form()
		
	def form(self):
		try:
			new = self.types.get(self.shape)(self.size)
			return new
		except Exception:
			raise
		
	def reset(self, new_colors):
		"""
		Replaces the current palette with a new one
		
		@return: New palette ID's
		"""
		glDeleteLists(1, len(new_colors))
		
		return self.construct(new_colors)
	
	def construct(self, colorset):
		tile_id = []
		for color in colorset:
			id = self.template.compile(color)
			tile_id.append(id)
		
		return tile_id		#TODO: See if this is used during execution
