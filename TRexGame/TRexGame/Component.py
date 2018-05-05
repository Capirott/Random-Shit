from Object import Object
from GameObject import GameObject


class Component(Object):

	def __init__(self, game_object, **kwargs):
		super().__init__(type(self), **kwargs)
		self.game_object = game_object
		self.components = []
		self.transform = game_object.transform

	def get_components(self, type):
		return [c for c in components if type(c) == type]


