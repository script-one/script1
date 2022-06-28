# source file: prog/fn.s1
import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), '..', 'sys'))
from s1 import *

def inc(x):                                        # (1) 
                                                   # (1) 
  return (x+1)                                     # (1) 
                                                   # (1) 
add=lambda x,y:(x+y)                               # (3) 
log('inc(2)=',inc(2))                              # (5) 
log('add(2,3)=',add(2,3))                          # (6) 

