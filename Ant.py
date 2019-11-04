import numpy as np
import pdb

class Ant(object):
	def __init__(self,x,y, dir, rules, tile):
		"""
		Ant Class, it has a position and an orientation, the ant will move depending on the instruction that the current tile color represents
		
		@param x, y: Ant Initial position
		@param dir: Initial orientation of the ant
		@param rules: Set of instructions that this particular ant follows
		@param tile: Type of tile used on the current session
		"""
	
		self.tile = tile
		self.dir = dir
		self.pos = np.array([x,y])
		self.ruleset = rules
			
	def command(self, index):
		"""
		Rotates ant and moves forward
		
		@param index: Index of the current instruction being porcessed
		"""
		self.dir = (self.dir + self.tile.offset.get(self.ruleset[index])) % len(self.tile.offset)
		self.pos += np.array(self.tile.directions.get(self.dir))
		