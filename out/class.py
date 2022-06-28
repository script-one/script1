# source file: prog/class.s1
import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), '..', 'sys'))
from s1 import *

class Person: 
                                                   # (2) 
  def __init__(self, name,age):                    # (2) 
                                                   # (2) 
    self.name=name                                 # (3) 
    self.age=age                                   # (4) 
   
                                                   # (6) 
  def __str__(self, ):                             # (6) 
                                                   # (6) 
    return (self.name+(' '+str(self.age)))         # (7) 
   
                                                   # (1) 
log(Person)                                        # (11) 
p= Person('ccc',52)                                # (13) 
log(str(p))                                        # (14) 
log(p)                                             # (15) 

