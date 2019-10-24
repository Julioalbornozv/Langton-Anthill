import numpy as np
import Ant as at
import random
import pdb

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
			first = file.readline()
			base = first.strip("\n").split("\t")[1]
			
			if base[0] == "K":
				base = self.random_ruleset(base[1:])
				
			for line in file:	##Cleanup this code
				data = line.strip("\n").split("\t")
				
				if len(data) == 4:	#Ruleset exists
					rule = data[3]
				else:
					rule = base
				
				if data[0] == "R":
					data[0] = random.randint(1,self.screen[0]-1)
				elif data[1] == "R":
					data[1] = random.randint(1,self.screen[1]-1)
				elif data[2] == "R":
					data[2] = random.randint(0,len(self.dir.keys()))
				
				bug = at.Ant(int(data[0])*self.size,
							int(data[1])*self.size,
							self.dir.get(int(data[2])), rule)
							
				self.ants.append(bug)
				
	def random_ruleset(self, specs):
		"""
		Generates a random set of instructions from the given specifications
		
		@param specs: 	String, first char defines what instructions will be used while the rest represent the number of elements the ruleset will have
		
		@returns:	String containing the new ruleset
		
		"""
		mode = specs[0]
		length = int(specs[1:])
		instructions = ["L","R","U","D"]	#TODO: Find a way to obtain this instructions
		rand_rule = ""
		for i in range(length):
			if mode == "N":
				ch = random.randint(0,1)
			elif mode == "E":
				ch = random.randint(0,3)
			rand_rule += instructions[ch]
		
		return rand_rule

		