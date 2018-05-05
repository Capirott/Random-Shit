from Behaviour import Behaviour

class MonoBehaviour(Behaviour):

	objects = []
	
	def update_all():
		for o in MonoBehaviour.objects:
			o.update()
	
	def __init__(self, game_object, **kwargs):
		super().__init__(game_object, **kwargs)
		MonoBehaviour.objects.append(self)
	
	def start(self):	
		pass
	
	def update(self):
		pass