from engine import Engine

import pygame

def main():
    dimension = int(input("Type the dimension of the game: "))
    grid = int(input("Type the grid of the game: "))
    food_score = int(input("Type the score for each food: "))
    bonus_score =int(input("Type the score for each bonus: "))
    snake_color = input("Type the snake color (green, blue, red, yellow, purple or orange): ")
    engine = Engine(dimension, grid, food_score, bonus_score, snake_color) #, pygame.FULLSCREEN | pygame.HWSURFACE | pygame.DOUBLEBUF)
    engine._exec_()    

if __name__ == "__main__":
    main()