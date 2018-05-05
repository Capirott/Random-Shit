from Object import Object

class Image():
	
	def __init__(self, **kwargs):
		self.height = 0
		self.width = 0
		self.sprite = None

	def set_src(self, sprite):
		self.sprite = sprite

