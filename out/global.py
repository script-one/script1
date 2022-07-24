# source file: prog/global.s1
import sys
import os
sys.path.append('sys')
from s1 import *

log('hello 你好!')                               # (1) 
x=3                                                # (3) 
glob.x=5                                           # (5) 
log('x=',x)                                        # (7) 
log('@x=',glob.x)                                  # (8) 

