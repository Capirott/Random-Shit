from event import *
from constant import *
from board import Board
from view import View
import pygame

class Map(EventObject): 
    
    def __init__(self, dimension, grid, player_color, food_score, bonus_score, flag = 0):       
        self.grid = grid
        self.food_score = food_score
        self.bonus_score = bonus_score
        self.view = View(dimension, self.grid, player_color, flag)
        self.board = Board(self.grid)
        self.connect(self.board, "grid_changed", self, "update_grid")
        self.connect(self, "update_view_at", self.view, "update_at")
        self.connect(self, "clear_grid",self.view, "clear_grid")
       
        self.reload()

    def direction_changed(self, direction):
        """
            This method is invoked by the Engine. Changing the direction of the map.
        """
        if self.direction == Directions.DOWN and direction == Directions.UP:
            return
        if self.direction == Directions.UP and direction == Directions.DOWN:
            return
        if self.direction == Directions.RIGHT and direction == Directions.LEFT:
            return
        if self.direction == Directions.LEFT and direction == Directions.RIGHT:
            return        
        self.direction = direction
    
    def reload(self):    
        """
            Restart the map. It clears the board and view, and also position the snake in the middle with size = grid / 3.
            One random food is placed, too.
        """
        self.direction = Directions.RIGHT
        self.prev_direction = Directions.RIGHT
        self.number_food_eaten = 0   
        self.number_obstacle_created = 0   
        self.prev_food = None
        self.clean_tongue = False    
        self.board.clear()
        self.view.clean_all()
        self.board.init_snake_in_middle(int(self.grid / 3))
        self.board.put_random_item(Types.FOOD)                   
    
    def update_grid(self, row, column, prev, new):
        """
            This method is a bridge between the board and the view.
            The board is updated, and then it invokes this method. Then this method does the calculating to tell the view which grid it is going to be draw.
        """ 
        ### If the previous type is equal the new one. No need to tell the view to update the same grid ###
        if prev == new:              
            return
        self.emit("clear_grid", [row, column])  ### Tells the view to clean this grid ###              
        if new == Types.SNAKE: ### The new item is a snake part ###
            ### Draws the head and the tongue ###         
            if self.direction == Directions.UP:                  
                    self.emit("update_view_at", [row, column, "mouth_up"])
                    tmp_item_position = self.board.round_position(row - 1, column)
                    if self.board.get_at(*tmp_item_position) == Types.FOOD:
                        self.prev_food = tmp_item_position      
                        self.emit("update_view_at", [*self.prev_food, "tongue_up"])
                        self.clean_tongue = False            
            elif self.direction == Directions.DOWN:                  
                    self.emit("update_view_at", [row, column, "mouth_down"])  
                    tmp_item_position = self.board.round_position(row + 1, column)
                    if self.board.get_at(*tmp_item_position) == Types.FOOD:
                        self.prev_food = tmp_item_position   
                        self.emit("update_view_at", [*self.prev_food, "tongue_down"])                            
                        self.clean_tongue = False               
            elif self.direction == Directions.RIGHT:             
                    self.emit("update_view_at", [row, column, "mouth_right"]) 
                    tmp_item_position = self.board.round_position(row, column + 1)     
                    if  self.board.get_at(*tmp_item_position) == Types.FOOD: 
                        self.prev_food = tmp_item_position     
                        self.emit("update_view_at", [*self.prev_food, "tongue_right"])                            
                        self.clean_tongue = False            
            elif self.direction == Directions.LEFT:                     
                    self.emit("update_view_at", [row, column, "mouth_left"])   
                    tmp_item_position = self.board.round_position(row, column - 1)
                    if self.board.get_at(*tmp_item_position) == Types.FOOD:                        
                        self.prev_food = tmp_item_position
                        self.emit("update_view_at", [*self.prev_food, "tongue_left"])                          
                        self.clean_tongue = False  
            ### End of drawing head and tongue code ###               
            if len(self.board.snake) > 1:                   
                ### Clean grid to replace for tail ###
                self.emit("clear_grid", [*self.board.get_snake_tail()]) 
                tail_direction = self.board.get_tail_direction()
                if tail_direction == Directions.RIGHT:
                    self.emit("update_view_at", [*self.board.get_snake_tail(), "tail_right"])      
                elif tail_direction == Directions.LEFT:
                    self.emit("update_view_at", [*self.board.get_snake_tail(), "tail_left"])   
                elif tail_direction == Directions.UP:
                    self.emit("update_view_at", [*self.board.get_snake_tail(), "tail_up"]) 
                else:
                    self.emit("update_view_at", [*self.board.get_snake_tail(), "tail_down"]) 
                prev_row = self.board.snake[1][0]
                prev_column = self.board.snake[1][1]
                ### Clean the grid in the previous position ###
                self.emit("clear_grid", [prev_row, prev_column])                     
                if self.direction != self.prev_direction: ### Direction changed the prev grid will be a body turn ###
                        if (self.prev_direction == Directions.UP and self.direction == Directions.LEFT) or \
                    (self.prev_direction == Directions.RIGHT and self.direction == Directions.DOWN):                            
                            self.emit("update_view_at", [prev_row, prev_column, "turn_1"])                        
                        elif (self.prev_direction == Directions.UP and self.direction == Directions.RIGHT) or \
                    (self.prev_direction == Directions.LEFT and self.direction == Directions.DOWN):                            
                            self.emit("update_view_at", [prev_row, prev_column, "turn_2"])                    
                        elif (self.prev_direction == Directions.DOWN and self.direction == Directions.RIGHT) or \
                    (self.prev_direction == Directions.LEFT and self.direction == Directions.UP):                            
                            self.emit("update_view_at", [prev_row, prev_column, "turn_4"])                        
                        elif (self.prev_direction == Directions.DOWN and self.direction == Directions.LEFT) or \
                    (self.prev_direction == Directions.RIGHT and self.direction == Directions.UP):                            
                            self.emit("update_view_at", [prev_row, prev_column, "turn_3"])
                else:   
                    ### Direction didn't change, the snake body will be a horizontal or vertical one ###
                    if self.direction == Directions.UP or self.direction == Directions.DOWN:
                        self.emit("update_view_at", [prev_row, prev_column, "vertical"])
                    else:
                        self.emit("update_view_at", [prev_row, prev_column, "body_horizontal"])   
            if self.prev_food != None: ### Used only for removing the tongue in the threatened food ###
                if self.clean_tongue == True and self.board.get_at(*self.prev_food) == Types.FOOD:
                    self.emit("clear_grid", [*self.prev_food])
                    self.emit("update_view_at", [*self.prev_food, "food"]) 
                    self.prev_food = None             
                else: ### clean_tongue set True because it will be removed in the next movement ###
                    self.clean_tongue = True         
        elif new == Types.FOOD: ### The new item added was a food ###            
            self.emit("update_view_at", [row, column, "food"])                     
        elif new == Types.BAIT:
            self.emit("update_view_at", [row, column, "bait"]) 
            
    def advance(self):
        """ 
            This method is invoked by the Engine. Making the snake to move.
        """                
        snake_head = self.board.get_snake_head() ### This method returns a copy ###
        if self.direction == Directions.UP:
            snake_head[0] -= 1
        elif self.direction == Directions.DOWN:
            snake_head[0] += 1
        elif self.direction == Directions.RIGHT:
            snake_head[1] += 1
        elif self.direction == Directions.LEFT:
            snake_head[1] -= 1            
        snake_head = self.board.round_position(*snake_head)
        type_at_head = self.board.get_at(snake_head[0], snake_head[1], roundit = False)        
        if type_at_head == Types.SNAKE:
            self.emit("obstacle_hit") ### Notify that the snake hit a target ###
            return
        elif type_at_head == Types.BAIT:
            if self.direction == Directions.DOWN:
                self.emit("bait_eaten", [Directions.DOWN])
            else:
                self.emit("bait_eaten")
            return
        if type_at_head != Types.FOOD:
            self.board.remove_snake_tail()
        elif type_at_head == Types.FOOD:
            self.number_food_eaten += 1
            self.emit("food_eaten", [self.food_score]) ### Notify that the snake reached a food ###
            if self.number_food_eaten == 3:
                self.emit("bonus_won", [self.bonus_score])
                self.number_obstacle_created += 1
                self.number_food_eaten = 0
                self.board.put_random_item(Types.BAIT)
            self.board.put_random_item(Types.FOOD) ### Add a new food ###            
        self.board.put_snake_at(snake_head[0], snake_head[1]) ### Place the new head's position ###
        self.view.commit_changes()  ### Commit the changes to the view ###
        ### Keep previous direction for determinating if the snake turned ###
        self.prev_direction = self.direction
        print ("Direction: %s, Snake size: %i" % (self.direction, self.board.get_snake_size()))