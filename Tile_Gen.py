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
		@field: palette, List of colors values for each tile (0-255)
		"""
		self.palette = []
		self.size = size
	
	def load_palette(self, path = "colors.txt"):
		"""
		Loads a palette from a txt file
		
		@param: path, File path to be used
		"""
		temp = []
		with open(path, "r") as data:
			for line in data:
				temp.append(np.asarray(list(map(int, (line.strip("\n")).split("\t")))))
		
		self.palette = np.asarray(temp)
	
	def save_palette(self,path):
		"""
		Saves the current palette into a file
		
		"""
		f = open(path,"w")
		for color in self.palette:
			f.write(str(int(color[0]))+"\t"+str(int(color[1]))+"\t"+str(int(color[2]))+"\n")
		
	def random_palette(self, n):
		"""
		Generates a color palette of n random colors 
		
		@param: n, Number of colors to be generated
		"""
		colors = []
		for j in range(0,n):
			colors.append([random.randint(0,255),random.randint(0,255),random.randint(0,255)])
		
		self.palette = np.asarray(colors)
	
	def fill_palette(self, interp = True, shuffle = True):
		"""
		This method extends the existing palette to a target number of colors.
		
		If interp is set to True, it will generate colors by interpolating between each color given. If false, the program will repeat colors until the palette size meets the target.
		
		@param interp, Boolean
		
		@returns Numpy array with the new colorset
		"""
		n = len(self.palette)
		if interp:	#Generates color between the given ones
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
		
		if shuffle:
			np.random.shuffle(new)
			
		return new
		
	def generate_tiles(self, cell_size, save = True):
		"""
		Generates tiles using OpenGL Display lists and the colors provided by the color palette , it will return a list of glList indexes, which can be used by glCallList to draw them on the screen.
		
		@param cell_size, tile side length in pixels
		@param save, if True it will save the palette after its generated
		@return Index List
		"""
		n = len(self.palette)
		
		assert n >=2, "Colorset Error: Not enough colors given"
		
		if n < self.size:
			self.palette = self.fill_palette()
			
		elif n > self.size:
			self.palette = self.palette[:self.size]
			
		if save:
			self.save_palette("save/colors.txt")
		
		colors = self.palette / 255.0 #Normlizes colors
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
		
		
		
		
		
		
		
		
		