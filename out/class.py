# source file: prog/class.s1
import sys
import os
sys.path.append('sys')
from s1 import *

class Person: 
                                                   # (5) 
    def __init__(self, name,age):                  # (5) 
        self.name=name                             # (6) 
        self.age=age                               # (7) 

                                                   # (9) 
    def toString(self, ):                          # (9) 
        return (self.name+(' '+str(self.age)))     # (10) 

                                                   # (1) 
def main():                                        # (14) 
    log(Person)                                    # (15) 
    p=Person('ccc',52)                             # (17) 
    log(str(p))                                    # (18) 
    log(p)                                         # (19) 
                                                   # (14) 
if 'main' in globals():run(main)
