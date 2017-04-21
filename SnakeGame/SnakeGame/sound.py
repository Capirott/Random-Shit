from event import EventObject
from constant import Directions
import pygame
import os

SOUNDS_DIR = os.path.join(os.path.split(__file__)[0], "sounds")

class Sound(EventObject):

    def __init__(self):
        self.load_sounds()  
    
    
    def load_sounds(self):        
        pygame.mixer.music.load(os.path.join(SOUNDS_DIR, "background.mp3")) 
        self.play_music()
        pygame.mixer.music.set_volume(0.3)
        self.food_eaten = self.load_sound("food_eaten.wav")
        self.obstacle_hit = self.load_sound("obstacle_hit.wav")
        self.bonus_won = self.load_sound("bonus_won.wav")
        self.bait_eaten = self.load_sound("bait_eaten.wav")
        self.bait_eaten_down = self.load_sound("bait_eaten_down.wav")
    def load_sound(self, sound_name):
        full_name = os.path.join(SOUNDS_DIR, sound_name)
        if not pygame.mixer or not pygame.mixer.get_init():
            raise EnvironmentError("Could not get pygame mixer")
        try:
            sound = pygame.mixer.Sound(full_name)
        except(pygame.error):
            raise (SystemExit("Cannot load sound: %s" % full_name))
        return sound

    def play_food_eaten_sound(self, *args):   
        #pygame.mixer.stop()
        self.food_eaten.play()

    def play_obstacle_hit_sound(self, *args): 
        pygame.mixer.stop()
        self.pause_music()
        self.obstacle_hit.play()
    
    def play_bonus_won_sound(self, *args): 
        #pygame.mixer.stop()
        self.bonus_won.play()

    def play_bait_eaten_sound(self, *args):
        pygame.mixer.stop()
        self.pause_music()

        if len(args) > 0  and args[0] == Directions.DOWN:
            self.bait_eaten_down.play()
        else:    
            self.bait_eaten.play()

    def play_music(self):       
        pygame.mixer.stop() 
        pygame.mixer.music.play(-1, 0.0)

    def pause_music(self):    
        pygame.mixer.music.stop()          