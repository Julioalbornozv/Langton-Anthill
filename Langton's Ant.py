# coding=utf-8

#TODO: Integrate logging library
import pygame
import numpy as np
import sys
import os
import random
import time
import pdb
import Tile_Gen as tg
from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLU import *
from win32api import GetSystemMetrics

def init():
	#TODO Migrate from pygame to cyglfw
	#TODO Add Docstring
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

def Paint_path(map):
	"""
	Paint tiles from the current frame
	
	@param map: Dict((x,y) : ID), Dictionary which contain the position of the tiles and their respective color
	"""
	
	for coord in map.keys():
		hue = map.get(coord)
		if hue != 0:
			glPushMatrix()
			glTranslate(coord[0],coord[1],0)
			glCallList(hue)
			glPopMatrix()
			
#-------------------- Ant Class --------------------#
class Ant(object):
	#TODO: Add Docstring
	#TODO: Improve rotation logic
	
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

#-------------------- Parameter Extraction --------------------#

#TODO: Move parsing logic to its own object

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
	instructions = ["L","R","U","D"]	#Find a way to make it mutable
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
#TODO: Standardize x,y coordinates (Remove as many divisions as possible)
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

#-------------------- Program Logic ----------------------#
#---------------------------------------------------------#
init()
run = True

#-------------------- Tile Generation --------------------#
Tgen = tg.Tile_Generator(len(ruleset)-1)

assert scheme in ["R","L"]

if scheme == "R":
	Tgen.random_palette(len(ruleset)-1)
elif scheme == "L":
	Tgen.load_palette()
	
tiles = Tgen.generate_tiles(k)

#-------------------- Ant Generation --------------------#

#TODO: Move colony to its own object

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
		

#-------------------- Main Loop --------------------#

Map = dict({(0,0) : 0})	#Dictionary mapping the board  (Coord tuple : Tile_ID)
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
				print("N° of tiles painted: {} tiles".format(len(list(Map.keys()))))
				print("N° of tile ID's: {}".format(len(tiles)))
				print("Display took {} seconds to paint the screen".format(Disp_time))
				print("Algorithm took {} seconds to complete {} cycles".format(Alg_time,ppf))
				print("Algorithm took {} seconds to update {} ants on average".format(Update_time,len(Colony)))
					
	glClear(GL_COLOR_BUFFER_BIT)
	
	Ddt_1 = time.time()
	
	Paint_path(Map)
	
	Ddt_2 = time.time()
	Disp_time = Ddt_2 - Ddt_1
	
	Adt_1 = time.time()
	
	#TODO: Improve this code
	for iter in range(ppf):
		for ant in Colony:		#1 turn for each ant
			
			ant.dir %= 4
			
			pos = (ant.x, ant.y)
			
			color = Map.get(pos)
			if color == None:	#New tile is rendered
				color = 0
			
			Map.update({pos : (color+1) % (len(tiles)+1)})  #
				
			ant.command(ruleset[color])  #Move ant based on recovered rule
						
			ant.x %= ancho	#Wraps ant position
			ant.y %= alto
		
	Adt_2 = time.time()
	Alg_time = Adt_2-Adt_1
	Update_time = Alg_time/100
	pygame.display.flip()
	pygame.time.wait(int(1000/60)) #FPS
		