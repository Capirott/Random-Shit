from abc import ABC 

class Object(ABC):
	
	def __init__(self, name, **kwargs):
		super().__init__(**kwargs)
		self.name = str(name)




