# source file: prog/cond.s1
import sys
import os
sys.path.append('sys')
from s1 import *

max=lambda x,y:x if (x>y) else y                   # (1) 
log('max(3,5)=',max(3,5))                          # (3) 

