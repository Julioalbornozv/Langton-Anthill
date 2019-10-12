import numpy as np
import random
from OpenGL.GL import *
from OpenGL.GLU import *
import pdb

class Tile_Generator(object):
	def __init__(self, size):
		"""
		Class responsible to create the tiles which will be used by the program, currently this tiles are a set of gl
		
		@param: size, Expected number of colors to be generated
		@field: pallete, List of colors values for each tile (0-255)
		"""
		self.pallete = []
		self.size = size
	
	def load_pallete(self, path = "colors.txt"):
		"""
		Loads a pallete from a txt file
		
		@param: path, File path to be used
		"""
		temp = []
		with open(path, "r") as data:
			for line in data:
				temp.append(np.asarray(list(map(int, (line.strip("\n")).split("\t")))))
		
		self.pallete = np.asarray(temp)
		
	def random_pallete(self, n):
		"""
		Generates a color pallete of n random colors 
		
		@param: n, Number of colors to be generated
		"""
		for j in range(0,n):
			colors.append([random.random(),random.random(),random.random()])
		
		self.pallete = np.asarray(colors)
	
	def fill_pallete(self, autocomplete = False):
		"""
		This method extends the existing pallete to a target number of colors
		If autocomplete is set to True, the program will add colors between range of the colors given. If false, the program will repeat colors until the pallete size meets the target
		
		@param autocomplete, Boolean
		@returns Numpy array with the new colorset
		"""
		assert autocomplete == False, "Feature not implemented"
		
		if autocomplete:	#Generates color between the given ones
			
			"""
			req = n_colors-len(temp)
			gaps = np.zeros((len(temp)-1))
			gaps.fill(req//(len(temp)-1))
			
			gaps[:(req%(len(temp)-1))] += 1  #Add remainder
			
			gen = [0,0,0]
			#colors.append(temp[0])
			
			#TODO: Refactor using more numpy methods (arange)
			for i in range(len(temp)-1):
				for j in range(3):
					step = ((temp[i+1][j]-temp[i][j])//(gaps[i]+1)).astype(int)
					if step == 0:	#Same color
						gen[j] = [temp[i][j]]*(gaps[i].astype(int))
					else:
						gen[j] = list(range(temp[i][j],temp[i+1][j],step))
					
				t = list(zip(gen[0],gen[1],gen[2]))
				colors.extend(t)
			colors.append(temp[i+1])
			
			colors = np.asarray(colors) / 255.0
			"""
		else: 				# Repeats colors in order
			new = np.zeros((self.size,3))
			n = len(self.pallete)
			for i in range(self.size):
				new[i] = self.pallete[i%n]
			return new
			
	def generate_tiles(self, cell_size):
		"""
		Generates tiles using OpenGL Display lists and the colors provided by the color pallete , it will return a list of glList indexes, which can be used by glCallList to draw them on the screen.
		
		@param cell_size, tile side length in pixels
		@return Index List
		"""
		n = len(self.pallete)
		
		assert n >=2, "Colorset Error: Not enough colors given"
		
		if n < self.size:
			self.pallete = self.fill_pallete()
			
		elif n > self.size:
			self.pallete = self.pallete[:self.size]
			
		colors = self.pallete / 255.0 #Normlizes colors
		k = cell_size/2
		tileset = []
		
		for t_num in range(self.size):	
			tile = glGenLists(1)
			glNewList(tile,GL_COMPILE)
			glPushMatrix()
			
			glBegin(GL_QUADS)
			glColor3fv(colors[t_num])
			glVertex2fv([-k, -k])
			glVertex2fv([-k, k])
			glVertex2fv([k, k])
			glVertex2fv([k, -k])
			glEnd()
			
			glPopMatrix()
			glEndList()
			
			tileset.append(tile)
	
		return tileset
		
		
		
		
		
		
		
		
		