# source file: prog/class3.s1
import sys
import os
sys.path.append('sys')
from s1 import *

class Vehicle: 
    
                                                   # (4) 
    def honk(self, ):                              # (4) 
        return ''                                  # (5) 

                                                   # (1) 
class Car(Vehicle): 
                                                   # (11) 
    def honk(self, ):                              # (11) 
        log('BAAAAA')                              # (12) 

                                                   # (9) 
class SportsCar(Car): 
    
                                                   # (19) 
    def __init__(self, brand):                     # (19) 
        self.brand=brand                           # (20) 

                                                   # (16) 
def main():                                        # (24) 
    benzzz=SportsCar('Benzzz')                     # (25) 
    log(benzzz.brand)                              # (26) 
    benzzz.honk()                                  # (27) 
                                                   # (24) 
if 'main' in globals():run(main)
