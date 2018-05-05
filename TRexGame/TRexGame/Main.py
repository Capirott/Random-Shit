import pygame
from GameObject import GameObject
from Player import Player
from Sprite import Sprite
from SpriteRenderer import SpriteRenderer
from MonoBehaviour import MonoBehaviour
from PlayerController import PlayerController
from Renderer import Renderer
from Start import start
from Object import Object

(WIDTH, HEIGHT) = (1024, 600)
BACKGROUND_COLOUR = (255,255,255)
BLACK = (0, 0, 0)

def main():
	screen = pygame.display.set_mode((WIDTH, HEIGHT))
	pygame.display.set_caption('T-Rex Game')
	screen.fill(BACKGROUND_COLOUR)
	Renderer.screen = screen
	start()
	running = True
	while running:
		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				running = False
		MonoBehaviour.update_all()
		Renderer.render_all()
		pygame.display.flip()
	pygame.quit()


if __name__ == '__main__':
	main()