import numpy as np
import Ant as at
import random

class Colony(object):
	"""
	Ant container class, handles ant generation.
	
	@param config: Configuration parameters
	
	@field size: Tile Size in pixels
	@field screen: Size of the screen
	@field default: Default Ruleset
	@field sym: Symbols used to describe a ruleset
	@field length: Length of each ant ruleset
	@field dir: Dictionary containing unitary vectors for each direction
	@field ants: List containing the Ant objects
	"""
	def __init__(self, config, tile):
		
		self.screen = (config.getint('Display', 'WIDTH'), 
						config.getint('Display', 'HEIGHT'))
		self.default = config.get('Ruleset', 'DEFAULT')
				
		self.sym = list(config.get('Ruleset', 'SYMBOLS'))
		self.length = config.getint('Ruleset', 'LENGTH')
		self.save = config.getboolean('Ruleset', 'SAVE')
		
		self.Ttype = tile
		
		self.ants = []
		
		if self.default == 'RANDOM':
			self.default = self.random_ruleset()
		
	def load_ants(self, path):
		"""
		Loads ant data from a txt file
		
		@param: path, File path to be used
		"""
		with open(path, "r") as file:
			for line in file:
				data = line.strip("\n").split("\t")
				
				if len(data) == 4:	#Ruleset exists
					if data[3] == 'RANDOM':
						rule = self.random_ruleset()
					else:
						assert len(data[3]) == self.length, "Ruleset Error: Inconsistent ruleset size"
						rule = data[3]
				else:
					rule = self.default
				
				print(rule)
				if data[0] == "R":
					data[0] = random.randint(1,self.screen[0]-1)
				if data[1] == "R":
					data[1] = random.randint(1,self.screen[1]-1)
				if data[2] == "R":
					data[2] = random.randint(0,len(self.Ttype.directions.keys())-1)
				
				bug = at.Ant(int(data[0]) * self.Ttype.size,
							int(data[1]) * self.Ttype.size,
							int(data[2]), rule, self.Ttype)
							
				self.ants.append(bug)
				
		if self.save:
			self.save_ants("save/ants.txt")
	
	def save_ants(self, path):
		"""
		Saves data of generated ants in a backup txt file
		
		@param path: Location of the backup
		"""
		f = open(path,"w")
		dir = self.Ttype.directions
		size = self.Ttype.size
		for ant in self.ants:
			for k in dir.keys():
				if k== ant.dir:
					face = str(k)
					break
			f.write(str(ant.pos[0]//size)+"\t"+str(ant.pos[1]//size)+"\t"+face+"\t"+ant.ruleset+"\n")
		f.close()
		
		
		
	def random_ruleset(self):
		"""
		Generates a random set of instructions from the given specifications
		
		@returns:	String containing the new ruleset
		
		"""
		rand_rule = ""
		for i in range(self.length):
			ch = random.randint(0, len(self.sym)-1)
			rand_rule += self.sym[ch]
		
		return rand_rule

		