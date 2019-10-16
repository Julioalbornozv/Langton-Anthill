import numpy as np
import Ant as at
import random

class Colony(object):
	"""
	Ant container class, handles ant generation.
	
	@param dir: Dictionary containing unitary vectors for each direction
	@param size: Int, size of a tile
	@param screen_size: Tuple containing the dimensions of the screen
	
	@field ants: List containing the Ant objects
	
	"""
	def __init__(self, directions, cell_size, screen_size):
	
		self.dir = directions
		self.size = cell_size
		self.screen = screen_size
		self.ants = []
		
	def load_ants(self, path):
		"""
		Loads ant data from a txt file
		
		@param: path, File path to be used
		"""
		with open(path, "r") as file:
			for line in file:
				data = line.strip("\n").split("\t")
				if data[0] == "R":
					data[0] = random.randint(1,self.screen[0]-1)
				elif data[1] == "R":
					data[1] = random.randint(1,self.screen[1]-1)
				elif data[2] == "R":
					data[2] = random.randint(0,len(self.dir.keys()))
				
				bug = at.Ant(int(data[0])*self.size,
							int(data[1])*self.size,
							self.dir.get(int(data[2])))
							
				self.ants.append(bug)