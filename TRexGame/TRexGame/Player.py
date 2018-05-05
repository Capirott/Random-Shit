from GameObject import GameObject
from MonoBehaviour import MonoBehaviour

class Player(MonoBehaviour):

	def __init__(self, game_object, **kwargs):
		super().__init__(game_object, **kwargs)

	def start(self):
		super().start()

	def update(self):
		super(Player, self).update()



