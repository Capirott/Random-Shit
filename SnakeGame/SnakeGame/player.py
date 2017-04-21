from event import *

class Player(EventObject):
    
    def __init__(self):
        self.dict = {}
        self.dict["score"] = 0
        self.dict["live"] = False
        self.dict["speed"] = 0.1
        self.dict["color"] = "orange"

    def __getitem__(self, key):
        if key in self.dict.keys():
            return self.dict[key]
        else:
            raise KeyError("Player doesn't have %s to get" % key)

    def __setitem__(self, key, item):

               
        if not key in self.dict.keys():
            raise KeyError("Player Doesn't have %s to set" % key)
            
        self.dict[key] = item
        self.emit(key+"changed", [self.dict[key]])
        self.emit_dead_info()

    def is_dead(self):
        return self.dict["live"] == False
    
    def emit_dead_info(self):
        if self.is_dead():
            self.emit("dead")

    def obstacle_hit(self, *args):
        """
            This method is called from the map when the snake hits an obstacle.
        """
        self["live"] = False

    def food_eaten(self, food_points):        
        """
            This method is called from the map when a food is eaten.
        """
        self["score"] += food_points

    def bonus_won(self, bonus_points):
        """
            This methos is called from the map when a bonus is gained
        """
        self["score"] += bonus_points

    def bait_eaten(self, *args):
        """ 
            This method is called from the map when the snake eats a bait.
        """
        self["live"] = False
    