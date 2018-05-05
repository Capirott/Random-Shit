from GameObject import GameObject
from Player import Player
from SpriteRenderer import SpriteRenderer
from PlayerController import PlayerController

def start():
	player = GameObject("Player")
	player.add_component(SpriteRenderer)
	player.add_component(Player)
	player.add_component(PlayerController)