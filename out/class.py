# source file: prog/class.s1
import sys
import os
sys.path.append('sys')
from s1 import *

class Person: 
                                                   # (2) 
    def __init__(self, name,age):                  # (2) 
        self.name=name                             # (3) 
        self.age=age                               # (4) 

                                                   # (6) 
    def __str(self, ):                             # (6) 
        return (self.name+(' '+str(self.age)))     # (7) 

                                                   # (1) 
log(Person)                                        # (11) 
p=Person('ccc',52)                                 # (13) 
log(str(p))                                        # (14) 
log(p)                                             # (15) 

