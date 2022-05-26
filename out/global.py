# source file: prog/global.s1
import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), '..', 'sys'))
from s1 import *

global.log('hello 你好!');                       # (1) 
x=3;                                               # (3) 
global.x=5;                                        # (5) 
log('x=',x);                                       # (7) 
log('@x=',global.x);                               # (8) 

