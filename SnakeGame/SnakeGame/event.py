class EventManager():
    
    registry = []
    @staticmethod 
    def emit(sender, signal, args):
        for register in EventManager.registry:
            
            if (register[0] is sender) and (register[1] == signal):
                
                if not hasattr(register[2], register[3]):
                    continue
                
                function = getattr(register[2], register[3])
                function(*args)
    
    
    @staticmethod
    def connect(sender, signal, listener, slot):
        
        EventManager.registry.append([sender, signal, listener, slot])
    
    
    @staticmethod    
    def destroyListener(target):
        
        i = 0
        copy = EventManager.registry
        EventManager.registry = []
        
        while i < len(copy):
            
            if not (copy[i][0] is target or copy[i][2] is target):
                
                EventManager.registry.append(copy[i])                
            i += 1
          
class EventObject():
    
    def emit(self, signal, args=[]):
        
        EventManager.emit(self, signal, args)
        
        
    def connect(self, sender, signal, listener, slot):
        """
            Connects sender to listener
        """
        EventManager.connect(sender, signal, listener, slot)
        
        
    def disconnect(self):
        
        EventManager.destroyListener(self)
    