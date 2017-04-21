from event import *
from random import randint
import pygame
import os

IMAGES_DIR = os.path.join(os.path.split(__file__)[0], "images")

class View(EventObject):
    
    def __init__(self, dimension, grid, player_color, flag = 0):
        self.grid = grid
        self.dirties = []
        self.screen = pygame.display.set_mode([dimension, dimension], flag)
        self.dimension = dimension
        self.set_background(os.path.join(IMAGES_DIR, "background.png"))
        self.grid_size = int(dimension / grid)
        self.load_assets(player_color)  

    def set_background(self, imageFile):        
        surface = pygame.image.load(imageFile).convert()
        self.background = pygame.transform.scale(surface, [self.dimension, self.dimension])        
        self.screen.blit(self.background, (0, 0))
        self.dirties.append([0, 0, self.dimension, self.dimension])

    def commit_changes(self):
        """
            Update the changes made in the dirties list
        """        
        pygame.display.update(self.dirties)
        self.dirties = []

    def get_background_at(self, rect):
        
        image = pygame.Surface(rect.size).convert()
        image.blit(self.background, (0, 0) , rect)
        return image

    def update_at(self, row, column, new):
        rect = pygame.Rect(column * self.grid_size, row * self.grid_size,
                            self.grid_size, self.grid_size)
        self.dirties.append(rect)
        ### This value is used for moving the corner of the snake to the right place
        tmp = self.grid_size * 0.32 
        ### Mouth Up ###
        if new == "mouth_up":
            self.screen.blit(self.mouth_up, rect)
        ### Mouth Down ###
        elif new == "mouth_down":
            self.screen.blit(self.mouth_down, rect)
        ### Mouth Right ###
        elif new == "mouth_right":            
            self.screen.blit(self.mouth_right, rect)
        ### Mouth Left ###
        elif new == "mouth_left":
            self.screen.blit(self.mouth_left, rect)
        ### Right to Down or Up to Left ###
        elif new == "turn_1":
            self.screen.blit(self.turn_1, rect.move(-tmp, tmp))
        ### Right to Up or Down to Left ###
        elif new == "turn_3":
            self.screen.blit(self.turn_3, rect.move(-tmp, -tmp))
        ## Up to Right or Left to Down ###
        elif new == "turn_2":
            self.screen.blit(self.turn_2, rect.move(tmp, tmp))
        ### Down to Right or Left to Up ###
        elif new == "turn_4":
            self.screen.blit(self.turn_4, rect.move(tmp, -tmp))
        ### Food ###
        elif new == "food":            
            self.screen.blit(self.food[(rect.x + rect.y) % (len(self.food))], rect)
        elif new == "bait":
            self.screen.blit(self.bait[(rect.x + rect.y) % (len(self.bait))], rect)
        ### Body Horizontal ###
        elif new == "body_horizontal":
            self.screen.blit(self.body_horizontal, rect)       
        ### Body Vertical ### 
        elif new == "vertical":
            self.screen.blit(self.vertical, rect)
        ### Body Tail Right ###
        elif new == "tail_right":
            self.screen.blit(self.tail_right, rect)
        ### Body Tail Left ###
        elif new == "tail_left":
            self.screen.blit(self.tail_left, rect)
        ### Body Tail Down ###
        elif new == "tail_down":
            self.screen.blit(self.tail_down, rect)
        ### Body Tail Up ###
        elif new == "tail_up":
            self.screen.blit(self.tail_up, rect)
        ### Tongue Up ###
        elif new == "tongue_up":
            self.screen.blit(self.tongue_up, rect)
        ### Tongue Down ###
        elif new == "tongue_down":
                    self.screen.blit(self.tongue_down, rect)
        ### Tongue Right ###
        elif new == "tongue_right":
                    self.screen.blit(self.tongue_right, rect)
        ### Tongue Left ###
        elif new == "tongue_left":
                    self.screen.blit(self.tongue_left, rect)
    
    def load_image(self, name):
        image = pygame.image.load(os.path.join(IMAGES_DIR, name)).convert_alpha()          
        image = pygame.transform.scale(image, (self.grid_size, self.grid_size))
        return image

    def load_assets(self, color = "yellow"):
        
        self.food = [self.load_image("food.png"), self.load_image("food_2.png"), self.load_image("food_3.png")]

        self.bait = [self.load_image("bait.png"), self.load_image("bait_2.png"), self.load_image("bait_3.png")]
        
        self.body_horizontal = self.load_image(color + "BodyStraight.png")         
        self.vertical = pygame.transform.rotate(self.body_horizontal, 90)
        
        self.turn_1 = self.load_image(color + "BodyTurn.png")       
        self.turn_2 = pygame.transform.rotate(self.turn_1, 90)        
        self.turn_3 = pygame.transform.rotate(self.turn_1, -90)        
        self.turn_4 = pygame.transform.rotate(self.turn_1, 180)
       
        self.mouth_right = self.load_image(color + "HeadStraight.png")      
        self.mouth_up = pygame.transform.rotate(self.mouth_right, 90)        
        self.mouth_down = pygame.transform.rotate(self.mouth_right, -90)        
        self.mouth_left = pygame.transform.rotate(self.mouth_right, 180)

        self.tail_left = self.load_image(color + "Tail.png")
        self.tail_down = pygame.transform.rotate(self.tail_left, 90)
        self.tail_up = pygame.transform.rotate(self.tail_left, -90)
        self.tail_right = pygame.transform.rotate(self.tail_left, 180)

        self.tongue_right = self.load_image(color + "Tongue.png")
        self.tongue_up = pygame.transform.rotate(self.tongue_right, 90)
        self.tongue_down = pygame.transform.rotate(self.tongue_right, -90)
        self.tongue_left =  pygame.transform.rotate(self.tongue_right, 180)

    def clear_grid(self, row, column):
        """
            Clear the grid in the position row and column, to the background image.
            If background image is not declared, it will draw a black rectangle in it.
        """        
        rect = pygame.Rect(column * self.grid_size, row * self.grid_size,
                            self.grid_size,self.grid_size)
        if hasattr(self,"background"):
            img = self.get_background_at(rect)
            self.screen.blit(img, rect)
        else:
            pygame.draw.rect(self.screen, [0, 0, 0], rect)
        self.dirties.append(rect)

    def player_dead(self):
        #self.screen.fill(pygame.color.Color("white"))
        text = "Do you wanna play again? (y / n)"
        font = pygame.font.Font("somethingstrange.ttf", 28)
        font.set_italic(1)
        image = font.render(text, 1, (pygame.color.Color("red")))
        self.dirties = [image.get_rect(centerx = self.background.get_width() / 2, centery = self.background.get_height() / 2)]
        self.screen.blit(image, *self.dirties)
        self.commit_changes()

    def clean_all(self):
        self.screen.blit(self.background, self.background.get_rect())
        self.dirties = self.background.get_rect()
        self.commit_changes()