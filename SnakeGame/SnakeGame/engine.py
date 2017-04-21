from view import View
from player import Player
from map import Map
from constant import *
from event import *
import pygame 
from sound import Sound

class Engine(EventObject):
    
    def __init__(self, dimension, grid, food_score, bonus_score, snake_color, flag = 0):
        print ("Initializing Engine!")
        pygame.init()    
        self.player = Player()
        self.player["color"] = snake_color
        self.connect(self.player, "dead", self, "player_died") 
        self.fps = 0
        self.map = Map(dimension, grid, self.player["color"], food_score, bonus_score, flag)
        ### Connect the map for receiving events from the Engine ###
        self.connect(self, "advance", self.map, "advance")
        self.connect(self, "direction_changed", self.map, "direction_changed")  
        ### Engine receives events from the map ###
        self.connect(self.map, "food_eaten", self, "food_eaten")
        self.connect(self.map, "obstacle_hit", self, "obstacle_hit")

        ### Create Sound Class and connect the map with it ###
        self.sound = Sound()
        self.connect(self.map, "food_eaten", self.sound, "play_food_eaten_sound")
        self.connect(self.map, "obstacle_hit", self.sound, "play_obstacle_hit_sound")
        self.connect(self.map, "bonus_won", self.sound, "play_bonus_won_sound")
        self.connect(self.map, "bait_eaten", self.sound, "play_bait_eaten_sound")

        ### Connects the map with the player ###
        self.connect(self.map, "food_eaten", self.player, "food_eaten")
        self.connect(self.map, "bait_eaten", self.player, "bait_eaten")
        self.connect(self.map, "obstacle_hit", self.player, "obstacle_hit")
        self.connect(self.map, "bonus_won", self.player, "bonus_won")

        ### Connect the player with the view ###
        self.connect(self.player, "dead", self.map.view, "player_dead") 

        self.start_new_game()
        self.clock = pygame.time.Clock()
        self.key_locked = False ### Used for locking key for the next move to happen ###
        self.key_pending = [] ### Used for keeping pressed keys ###
  
        self.update_caption()

    def update_caption(self, string = ""):
        """
            Used only for updating the window caption.
        """
        if string == "dead":
            pygame.display.set_caption("You are dead! score: %i, fps: %.2f"\
                                    % (self.player["score"], self.fps))
        elif string == "paused": 
            pygame.display.set_caption("### Paused ### fps: %.2f" % self.fps)        
        else:
            pygame.display.set_caption("nf: %i, no: %i,  fs: %i, bs: %i, sp: %.2f, score: %i, fps: %.2f"\
                                    % (self.map.board.num_food, self.map.number_obstacle_created,self.map.food_score, self.map.bonus_score, self.player["speed"], self.player["score"], self.fps))
    
    def start_new_game(self):      
        """
            Starts a new game.
        """
        self.advance = True  
        self.player["live"] = True
        self.player["speed"] = 0.1 
        self.player["score"] = 0
        self.map.reload()
        self.sound.play_music()

    def _exec_(self):
        """ 
            Game event main loop.
        """
        ticks_last_frame_speed = pygame.time.get_ticks()
        ticks_last_frame_fps = pygame.time.get_ticks()
        frames = 0
        while True:
            frames += 1.0
            self.handle_pending_keys()
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    exit(0)
                if event.type == pygame.KEYDOWN:                    
                    if event.key == pygame.K_ESCAPE:
                        exit(0)
                    if self.player["live"] == 1: ### Keys for when player is alive ###
                        if event.key == pygame.K_SPACE:
                            if self.advance == True:
                                self.advance = False ### Set advance false for stopping the map ###
                                self.key_locked = True ### Lock key for not getting moves while paused ###
                                self.sound.pause_music() 
                            else:
                                self.advance = True ### Set advance true so the map can continue ###
                                self.key_pending = [] ### Clean the pending keys so the snake won't move after continuing the game ###
                                self.key_locked = False  ### Set locked keys for getting new keys ###  
                                self.sound.play_music() 
                        elif not self.key_locked and self.advance:
                            key = event.key
                            self.handle_key(key)
                        else:
                            self.key_pending.append(event.key)
                    else:   ### Keys for player dead screen ###
                        if event.key == pygame.K_y:
                            self.start_new_game()
                        elif event.key == pygame.K_n:
                            exit(0)
            t = pygame.time.get_ticks()
            delta_time = (t - ticks_last_frame_speed) / 1000.0
            if self.advance and delta_time >= self.player["speed"]:
                self.key_locked = False ### Unlock the key for new directions. ###
                self.emit("advance")
                ticks_last_frame_speed = t

            t = pygame.time.get_ticks()
            delta_time = (t - ticks_last_frame_fps) / 1000.0
            if (delta_time >= 1.0):
                self.fps = frames
                frames = 0
                ticks_last_frame_fps = t
                if self.advance == True:
                    self.update_caption()
                elif self.player["live"] == 1:
                    self.update_caption("paused")
                else:
                    self.update_caption("dead")
            self.clock.tick(60)

    def handle_pending_keys(self):
        """
            This method takes care of pending keys.
            Does nothing while key is locked.
        """
        for key in self.key_pending:
            if self.key_locked: 
                return
            self.key_pending.remove(key)
            self.handle_key(key)
            
    def player_died(self):
        """
            This method is called when the player live is set to 0.
        """
        self.update_caption("dead")
        self.advance = False

    def handle_key(self, key):
        """
           Send to the map the new direction. And locks the key.
        """
        if key == pygame.K_UP or key == pygame.K_w:
            self.emit("direction_changed", [Directions.UP])
            self.key_locked = True
        elif key == pygame.K_DOWN or key == pygame.K_s:
            self.emit("direction_changed", [Directions.DOWN])
            self.key_locked = True
        elif key == pygame.K_RIGHT or key == pygame.K_d:
            self.emit("direction_changed", [Directions.RIGHT])
            self.key_locked = True
        elif key == pygame.K_LEFT or key == pygame.K_a:
            self.emit("direction_changed", [Directions.LEFT])
            self.key_locked = True
