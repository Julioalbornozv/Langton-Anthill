import numpy as np

class Ant(object):
	"""
	Ant Class, it has a position and an orientation, the ant will move depending on the instruction that the current tile color represents
	
	@param x, y: Coordinates
	@param dir: Orientation
	@param k: Tile size
	"""
	
	def __init__(self,x,y,dir):
		self.pos = np.array([x,y])
		self.dir = np.array(dir)
		
	def rot(self,theta):
		"""
		Calculates new orientation base on the rotation angle
		"""
		return np.array([[np.cos(theta), -np.sin(theta)],[np.sin(theta), np.cos(theta)]]).astype(int)
		
	def command(self, theta):
		"""
		Rotates ant and moves forward
		"""
		self.dir = np.dot(self.dir, self.rot(theta))
		self.pos += self.dir