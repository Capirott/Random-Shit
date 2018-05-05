from Object import Object

class Transform:
	def __init__(self, **kwargs):
		super().__init__(**kwargs)
		self.x = float(0.0)
		self.y = float(0.0)
		self.z = float(0.0)

class GameObject(Object):
	count = 0
	objects = []

	def __init_subclass__(*args, **kwargs):
		return super().__init_subclass__(**kwargs)

	def __init__(self, name, **kwargs):
		super().__init__(name, **kwargs)
		self.components = {}
		self.transform = Transform()
		GameObject.objects.append(self)

	def add_component(self, comp):
		new_component = comp(self) 
		self.components[type(comp)] = new_component
		return new_component

	def get_component(self, compType):
		return self.components[compType]

	