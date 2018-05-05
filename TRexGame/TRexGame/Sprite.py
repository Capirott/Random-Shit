import pygame
from GameObject import GameObject
from MonoBehaviour import MonoBehaviour
from Object import Object

class Sprite(Object):
	image = None
	hide = False

	def __init__(self, **kwargs):
		super().__init__('Sprite', **kwargs)
		self.image = pygame.image.load('res/dino.png').convert_alpha()
	
	def execute(self):
		#screen.blit
		(self.image, (self.game_object.transform.x, self.game_object.transform.y))

	def set_game_object(self, game_object):
		self.game_object = game_object


	


