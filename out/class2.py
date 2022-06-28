# source file: prog/class2.s1
import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), '..', 'sys'))
from s1 import *

class Person: 
  
  
                                                   # (5) 
  def __init__(self, name,age):                    # (5) 
                                                   # (5) 
    self.name=name                                 # (6) 
    self.age=age                                   # (7) 
   
                                                   # (9) 
  def toString__(self, ):                          # (9) 
                                                   # (9) 
    return (self.name+(' '+str(self.age)))         # (10) 
   
                                                   # (1) 
def main():                                        # (14) 
                                                   # (14) 
  log(Person)                                      # (15) 
  p= Person('ccc',52)                              # (17) 
  log(str(p))                                      # (18) 
  log(p)                                           # (19) 
                                                   # (14) 

