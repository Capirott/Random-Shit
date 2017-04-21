from event import *
from constant import *
from random import randint

class Board(EventObject):
    
    def __init__(self, grid):
        """
            Constructor of the new board.
            Grid is the size of the board.
        """
        self.row = grid
        self.column = grid
        self.board = []
        self.snake = []
        self.num_empty = 0
        self.num_bait = 0
        self.num_food = 0        

        self.connect(self, "grid_changed", self, "grid_changed_callback")
        for i in range(self.row):            
            self.board.append([])            
            for j in range(self.column):                
                self.board[i].append(Types.EMPTY)
                self.num_empty += 1


    def grid_changed_callback(self, row, column, prev, new):     
        """
            Updates the board based on the events
        """   
        if prev == new: 
            return 
        if prev == Types.SNAKE:
            for i in range(len(self.snake)):                
                if self.snake[i] == [row, column]: 
                    self.snake.pop(i)
                    break        
        elif prev == Types.EMPTY:    
            self.num_empty -= 1
            self.num_bait -= 1    
        if new == Types.EMPTY:       
            self.num_empty += 1
        elif new == Types.SNAKE:     
            self.snake.insert(0, [row,column])
        elif new == Types.FOOD:      
            self.num_food += 1
        elif new == Types.BAIT:
            self.num_bait += 1
    
    def round_position(self, row, column):
        """ 
            Rounds the position to a valid one.
        """
        if row >= self.row: 
            row = self.row % row
        elif row < 0:
            row = self.row + row
        if column >= self.column: 
            column = self.column % column 
        elif column < 0:
            column = self.column + column
        
        return row, column       

    def get_at(self, row, column, roundit = True):     
        """
            Get the value type of the item in the board position.
            The parameter roundit is used to transit the position to the begining.
            For example, imagine a board of size 300x300, if row is 301 and column is 200
            It will return the value in board[1, 200]
            Default value for roundit is True
        """   
        if roundit:
            row, column = self.round_position(row, column)
        elif row >= self.row or column >= self.column or row < 0 or column < 0: 
            return None
        return self.board[row][column]
    
    def put_snake_at(self, row, column):
        """
           Add a new position to the snake in the board. The new position becomes the head.
        """
        prev = self.board[row][column]
        if prev != Types.SNAKE:
            self.board[row][column] = Types.SNAKE
             ### Notify listeners that a new position was added ###
            self.emit("grid_changed", [row, column, prev,Types.SNAKE])
    
    def remove_snake_tail(self):
        """
            Removes the last position of the snake
        """        
        if len(self.snake) <= 0: 
            return        
        tail = self.snake.pop()
        self.board[tail[0]][tail[1]] = Types.EMPTY
        ### Notify listeners that the tail's grid was removed ###
        self.emit("grid_changed", [tail[0], tail[1], Types.SNAKE, Types.EMPTY])

    def clear_grid(self,row,column):        
        """
            Clean the board completely
        """
        prev = self.board[row][column]        
        if prev != Types.Empty:            
            self.board[row][column] = Types.EMPTY
            ### Notify listeners that the grid was removed ###
            self.emit("grid_changed", [row, column, prev, Types.EMPTY])
            
    
    def get_snake_head(self):        
        """
            Get a copy of the head's position
        """
        if len(self.snake) > 0:
            return [self.snake[0][0], self.snake[0][1]]
        
    def init_snake_in_middle(self, size = 3, direction = Directions.RIGHT):
        """
            Initialization of the snake in the middle of the screen, default size is 3 and direction to the right 
        """        
        midrow = int(self.row / 2)
        midcolumn = int(self.column / 2)        
        """
            It is important to put pieces from tail to head, because head is always the one which is added last!
            All of this POG means that we are putting the snake from the tail
            to the head! For example, when size = 3, range(-size + 1,1) will generate
            -2, -1, 0
        """        
        for i in range(-size + 1, 1):
            if direction == Directions.UP:
                self.put_snake_at(midrow + i, midcolumn)
            elif direction == Directions.DOWN:
                self.put_snake_at(midrow - i, midcolumn)
            elif direction == Directions.RIGHT:
                self.put_snake_at(midrow, midcolumn + i )
            elif direction == Directions.LEFT:
                self.put_snake_at(midrow, midcolumn - i)

    def get_snake_tail(self):
        """
            Returns a copy of the snake's tail
        """
        return [self.snake[-1][0], self.snake[-1][1]]

    def is_tail(self, row, column):
        """
            If the type in the position informed is the tail. Returns True, otherwise False.
        """
        return [self.round_position(row, column)] == self.snake[-1]

    def get_tail_direction(self):
        tail = self.snake[-1]
        sub_tail = self.snake[-2]
        dif = [tail[0] - sub_tail[0], tail[1] - sub_tail[1]]
        if dif[0] == 0:
            if dif[1] >= 0 and dif[1] < self.column - 1 or -dif[1] == (self.column - 1):
                return Directions.RIGHT
            else:
                return Directions.LEFT
        elif  dif[0] >= 0 and dif[0] < self.row - 1 or -dif[0] == (self.row - 1):
            return Directions.DOWN
        else:
            return Directions.UP
        
    def clear(self):        
        self.num_bait = 0
        self.num_food = 0
        for i in range(self.row):            
            for j in range(self.column):                
                old = self.board[i][j]                
                if old != Types.EMPTY:                    
                    self.board[i][j] = Types.EMPTY
                    self.emit("grid_changed",[i ,j, old, Types.EMPTY])
    
    def get_snake_size(self):
        return len(self.snake)

   
    def put_random_item(self, type):
    
        if self.num_empty <= 0: 
            return        
        rand_row = randint(0, self.row - 1)
        rand_column = randint(0, self.column - 1)        
        while self.board[rand_row][rand_column] != Types.EMPTY:
            rand_row = randint(0, self.row -1)
            rand_column = randint(0, self.column - 1)        
        self.board[rand_row][rand_column] = type        
        self.emit("grid_changed", [rand_row, rand_column, Types.EMPTY, type])