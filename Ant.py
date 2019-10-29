import numpy as np
import pdb

class Ant(object):
	"""
	Ant Class, it has a position and an orientation, the ant will move depending on the instruction that the current tile color represents
	
	@param x, y: Coordinates
	@param ruleset: Set of instructions that this particular ant follows
	"""
	
	def __init__(self,x,y, dir, rules, tile):
		self.tile = tile
		self.dir = dir
		self.pos = np.array([x,y])
		self.ruleset = rules
			
	def command(self, index):
		"""
		Rotates ant and moves forward
		"""
		#pdb.set_trace()
		self.dir = (self.dir + self.tile.offset.get(self.ruleset[index])) % len(self.tile.offset)
		self.pos += np.array(self.tile.directions.get(self.dir))
		