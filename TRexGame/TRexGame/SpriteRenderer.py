from Renderer import Renderer

class SpriteRenderer(Renderer):

	def __init__(self, game_object, **kwargs):
		super().__init__(game_object, **kwargs)
		self.color = (255,200,200)

	def render(self):
		super().render()
		if self.screen != None:
			print('render')