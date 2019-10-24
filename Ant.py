import numpy as np

class Ant(object):
	"""
	Ant Class, it has a position and an orientation, the ant will move depending on the instruction that the current tile color represents
	
	@param x, y: Coordinates
	@param dir: Orientation
	@param ruleset: Set of instructions that this particular ant follows
	"""
	
	def __init__(self,x,y,dir,rules):
		self.pos = np.array([x,y])
		self.dir = np.array(dir)
		self.ruleset = rules
		
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