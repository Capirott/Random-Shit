
from Component import Component

class Renderer(Component):
	objects = []
	screen = None
	def __init__(self, game_object, **kwargs):
		super().__init__(game_object, **kwargs)
		Renderer.objects.append(self)
	
	def render_all():
		for o in Renderer.objects:
			o.render()

	def render(self):
		pass