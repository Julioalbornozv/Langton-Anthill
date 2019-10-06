# coding=utf-8

import pygame
import numpy as np
import sys
import os
import random
import time
import pdb
from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLU import *
from win32api import GetSystemMetrics

def init():
	if full:
		os.environ['SDL_VIDEO_WINDOW_POS'] = '0,0'
	
	pygame.init()
	pygame.display.set_mode((ancho, alto), OPENGL| DOUBLEBUF)
	pygame.display.set_caption("Langton's Ant")
	
	glViewport(0, 0, ancho, alto)
	glMatrixMode(GL_PROJECTION)
	glLoadIdentity()
	gluOrtho2D(0.0, ancho, 0.0, alto)
	glMatrixMode(GL_MODELVIEW)
	glLoadIdentity()

	glClearColor(0.0, 0.0, 0.0, 0.0)	
	glShadeModel(GL_SMOOTH)
	glClearDepth(1.0)
	return

def Gen_Tiles(k,n_colors,scheme):
	"""
	Generates a list containing the color tiles the simulation will use
	
	k: Integer, cell size
	n_colors: Number of colors to be used
	scheme: Color mode to follow
	
	@return List containing colored tiles
	"""
	
	## Color Generation
	temp, colors, tileset = [], [], []
	if scheme == "L":	#Load Colors from colors.txt
		with open("colors.txt", "r") as data:
			for line in data:
				temp.append(np.asarray(list(map(int, (line.strip("\n")).split("\t")))))
		
		temp = np.asarray(temp)
		if len(temp) < n_colors:
			# If not enough colors are provided, this section should generate a pallete based on the given colors #TODO Move to its own method
			req = n_colors-len(temp)
			gaps = np.zeros((len(temp)-1))
			gaps.fill(req//(len(temp)-1))
			
			gaps[:(req%(len(temp)-1))] += 1  #Add remainder
			
			gen = [0,0,0]
			#colors.append(temp[0])
			
			#TODO Refactor using more numpy methods (arange)
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
				
		else:
			colors = temp / 255.0
			
			
	elif scheme == "R":	#Generates a random color pallete
		for j in range(0,n_colors):
			colors.append([random.random(),random.random(),random.random()])
		
		colors = np.asarray(colors)/255.0
	
	#pdb.set_trace()
	#assert n_colors == len(colors)
	for t_num in range(n_colors):	
		tile = glGenLists(1)
		glNewList(tile,GL_COMPILE)
		glPushMatrix()
		
		glBegin(GL_QUADS)
		glColor3fv(colors[t_num])
		glVertex2fv([-(k/2), -(k/2)])
		glVertex2fv([-(k/2), (k/2)])
		glVertex2fv([k/2, k/2])
		glVertex2fv([k/2, -(k/2)])
		glEnd()
		
		glPopMatrix()
		glEndList()
		
		tileset.append(tile)
	
	return tileset
	
def Paint_path(k,path,colors,buffer):
	"""
	Paint stored tiles from path
	"""
	if path == []:
		path.extend(buffer)
		return path
	for i in range(len(path)):
		if path[i] in buffer:
			buffer.remove(path[i])
			
		mx = path[i][0]//k
		my = path[i][1]//k
		if colors[my][mx] != 0:
			glPushMatrix()
			glTranslate(path[i][0],path[i][1],0)
			glCallList(colors[my][mx])
			glPopMatrix()
			
	path.extend(buffer)
	return path

"""
Ant Class
"""
class Ant(object):
	def __init__(self,x,y,dir,k):
		self.x = x
		self.y = y
		self.dir = dir
		self.k = k	#Length of a step
		self.orders = ((-1,0),(0,1),(1,0),(0,-1))
	
	def command(self, com):
		if com == "L":
			self.left()
		elif com == "R":
			self.right()
		elif com == "U":
			self.up()
		elif com == "D":
			self.down()
			
	def left(self):
		self.x += self.orders[self.dir][0]*self.k
		self.y += self.orders[self.dir][1]*self.k
		
		self.dir -= 1
			
	def right(self):
		self.x -= self.orders[self.dir][0]*self.k
		self.y -= self.orders[self.dir][1]*self.k	
		
		self.dir += 1
		
	def up(self):	
		self.y -= self.orders[self.dir][0]*self.k
		self.x += self.orders[self.dir][1]*self.k	
			
	def down(self):	
		self.y += self.orders[self.dir][0]*self.k
		self.x -= self.orders[self.dir][1]*self.k	
		
		self.dir += 2
"""
Starting Parameters
"""
Param = []
Colony = []		#Stores all declared ants

file = open("Parameters_Ant.txt","r")
for line in file:
	raw = line.replace("\n","")
	l = raw.split("\t")
	
	if l[0] == "ANT":	#Ant declaration
		Colony.append(l)
	elif l[0] == "COLOR":
		scheme = l[1]
	else:
		Param.append(l[1])

dim = int(Param[0])
height = int(Param[1])
k = int(Param[2])
ruleset = Param[3]

if ruleset[0] == "K":	#Random ruleset
	mode = ruleset[1]
	length = int(ruleset[2:])
	instructions = ["L","R","U","D"]	#Try to make it mutable
	rand_rule = ""
	for i in range(length):
		if mode == "N":
			ch = random.randint(0,1)
		elif mode == "E":
			ch = random.randint(0,3)
		rand_rule += instructions[ch]
	
	ruleset = rand_rule
	
print(ruleset)
		
assert len(ruleset) > 1, "Rulesets must contain at least 2 instructions"

#Sets screen size when requested
full = False

if dim == -1 and height == -1:
	full = True

if dim == -1:
	dim = GetSystemMetrics(0)//k

if height == -1:
	height = GetSystemMetrics(1)//k

#Visual Display
ancho = int(dim*k)
alto = int(height*k)	

"""
Main Loop
"""	
init()
run = True

#Generate tiles to be used
tiles = Gen_Tiles(k,len(ruleset)-1,scheme)

#Generate ants
if Colony == []: #No ants found
	Colony = [Ant(int(ancho/2),int(alto/2),"E",k,)]	#Ant placed at default position
else:
	a = 0
	for dec in Colony:
		if dec[1] == "R":
			dec[1] = random.randint(1,dim-1)
		if dec[2] == "R":
			dec[2] = random.randint(1,height-1)
		if dec[3] == "R":
			dec[3] = random.randint(0,3)
		
		#Initializes ants
		Colony[a] = Ant(int(dec[1])*k,int(dec[2])*k,int(dec[3]),k)		
		a += 1
		
		
path = []
Color_ID = np.zeros((height,dim),dtype = int)
buffer = []
hide_ant = True
ppf = 50	#Iterations per frame

Disp_time = 0
Alg_time = 0
Update_time = 0

while(run):	
	for event in pygame.event.get():
		if event.type == QUIT:
			run = False
	
		if event.type == KEYDOWN:
			if event.key == K_ESCAPE:
				run = False
			elif event.key == K_w:
				ppf += 10
				if ppf > 100:
					ppf = 100
			elif event.key == K_s:
				ppf -= 10
				if ppf < 0:
					ppf = 0
			elif event.key == K_p:		#Performance check #TODO Move this to its own test environement
				print("-------------------------------------------------------")
				print("N° of tiles painted: {} tiles".format(len(path)))
				print("N° of tile ID's: {}".format(len(tiles)))
				print("Display took {} seconds to paint the screen".format(Disp_time))
				print("Algorithm took {} seconds to complete {} cycles".format(Alg_time,ppf))
				print("Algorithm took {} seconds to update {} ants on average".format(Update_time,len(Colony)))
					
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
	
	Ddt_1 = time.time()
	path = Paint_path(k,path,Color_ID,buffer)
	Ddt_2 = time.time()
	Disp_time = Ddt_2 - Ddt_1
	
	Adt_1 = time.time()
	for iter in range(ppf):
		for ant in Colony:		#1 turn for each ant
			
			ant.dir = ant.dir % 4
			
			mx = ant.x//k
			my = ant.y//k
			
			
			color = Color_ID[my][mx]
			Color_ID[my][mx] = (Color_ID[my][mx]+1)%(len(tiles)+1)
			ant.command(ruleset[color])
						
			ant.x = ant.x % (ancho)
			ant.y = ant.y % (alto)
			
			if (ant.x,ant.y) not in buffer:
				buffer.append((ant.x,ant.y))
		
	Adt_2 = time.time()
	Alg_time = Adt_2-Adt_1
	Update_time = Alg_time/100
	pygame.display.flip()
	pygame.time.wait(int(1000/60)) #FPS
		