import numpy as np
import random

class Color_Generator(object):
	def __init__(self, config):
		"""
		Class responsible to create the tiles which will be used by the program, currently this tiles are a set of gl
		
		@param config: Configuration parameters
		
		@field size: Ruleset length
		@field base: Number of colors used to generate the colors
		@field interp: Color interpolation method
		@field shuffle: Determines if the generated colors are shuffled after generation
		@field save: Determines if generated data is saved after the simulation
		@field cell_size: Tile size in Pixels
		@field: palette, List of colors values for each tile (0-255)
		
		"""
		self.size = config.getint('Ruleset', 'LENGTH')-1
		self.interp = config.get('Color', 'INTERPOLATION')
		self.shuffle = config.getboolean('Color', 'SHUFFLE')
		self.save = config.getboolean('Color', 'SAVE')
		self.base = config.getint('Color', 'BASE')
		self.palette = []
		
		scheme = config.get('Color', 'SCHEME')
		
		if scheme == "RANDOM":
			self.random_palette(self.base)
		elif scheme == "LOAD":
			self.load_palette()
			
		self.generate_colors()
		
	def load_palette(self, path = "colors.txt"):
		"""
		Loads a palette from a txt file
		
		@param path: Path of the ant source file
		"""
		temp = []
		with open(path, "r") as data:
			for line in data:
				temp.append(np.asarray(list(map(int, (line.strip("\n")).split("\t")))))
		
		self.palette = np.asarray(temp)
	
	def save_palette(self,path):
		"""
		Saves the current palette into a file
		
		@param path: Path of the backup file
		"""
		f = open(path,"w")
		for color in self.palette:
			f.write(str(int(color[0]))+"\t"+str(int(color[1]))+"\t"+str(int(color[2]))+"\n")
		f.close()
		
	def random_palette(self, n):
		"""
		Generates a random color palette 
		
		@param n; Number of colors to generate
		"""
		colors = []
		for j in range(0,n):
			colors.append([random.randint(0,255),random.randint(0,255),random.randint(0,255)])
		
		self.palette = np.asarray(colors)
	
	def fill_palette(self):
		"""
		This method extends the existing palette to a target number of colors.
		
		@returns Numpy array with the new colorset
		"""
		n = len(self.palette)
		if self.interp == "RGB":	#Generates color between the given ones
			req = self.size - n
			gaps = np.zeros((n - 1))
			gaps.fill(req // (n - 1))
			
			gaps[:(req % (n - 1))] += 1  #Add remainder
			
			gen = [0,0,0]
			colors = []
			
			for i in range(n-1):
				for j in range(3):
					gen[j] = np.linspace(self.palette[i][j], self.palette[i+1][j], gaps[i]+1, endpoint=False)
				t = list(zip(gen[0],gen[1],gen[2]))
				colors.extend(t)
			
			colors.append(self.palette[-1]) #Adds last color
			new = np.asarray(colors)
			
		else: 				# Repeats colors in order
			new = np.zeros((self.size,3))
			for i in range(self.size):
				new[i] = self.palette[i%n]
		
		if self.shuffle:
			np.random.shuffle(new)
			
		return new
	
	def generate_colors(self):
		"""
		Generates tiles using OpenGL Display lists and the colors provided by the color palette , it will return a list of glList indexes, which can be used by glCallList to draw them on the screen.
		
		@return Index List
		"""
		n = len(self.palette)
		
		if n < self.size:
			self.palette = self.fill_palette()
			
		elif n > self.size:
			self.palette = self.palette[:self.size]
			
		if self.save:
			self.save_palette("save/colors.txt")
		
		
		
		
		
		
		