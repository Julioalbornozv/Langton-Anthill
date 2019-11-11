import numpy as np
import Tile
from OpenGL.GL import *
from OpenGL.GLU import *

class Tile_Generator(object):
	def __init__(self, config):
		"""
		Class responsible of loading the requested tile type and render it when needed. When adding a new tile shape, the self.types dictionry must be updated with the Tile name and constructor.
		
		@param config: Config object containing starting parameters
		
		@field scale: Tile scale factor
		@field shape: Requested tile shape
		@field types: Dictionary containing the currently available Tile object types and their associated names
		@field template: Generic tile which is given to other objects as a template
		"""
	
		self.scale = config.getint('Tile', 'SCALE')
		self.shape = config['Tile']['SHAPE']
		
		self.types = dict({"SQUARE": Tile.Square_Tile, "HEXAGON": Tile.Hexagonal_Tile})
		
		self.template = self.form()
		
	def form(self):
		"""
		Initializes a Tile object, if the shape requested is not known it will raise an error.
		"""
		try:
			new = self.types.get(self.shape)(self.scale)
			return new
		except Exception:
			raise
		
	def reset(self, colors):
		"""
		Deletes previous Tile instances, creates a new set based on the colors given
		
		@param colors: New colorset
		
		@return: New Tileset OpenGL ID's
		"""
		glDeleteLists(1, len(colors))
		
		return self.construct(colors)
	
	def construct(self, colorset):
		"""
		For each color given, the generator will instance a Tile by calling the OpenGL commands used on its construction + its color
		
		@return: Tileset OpenGL ID list
		"""
		tile_id = []
		for color in colorset:
			id = self.template.compile(color)
			tile_id.append(id)
		
		return tile_id	
