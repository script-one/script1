# source file: prog/if.s1
import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), '..', 'sys'))
from s1 import *

def max(x,y):                                      # (1) 
                                                   # (1) 
  return x if (x>y) else y                         # (1) 
                                                   # (1) 
min=lambda x,y:x if (x<y) else y                   # (2) 
log('max(3,5)=',max(3,5))                          # (4) 
log('min(3,5)=',min(3,5))                          # (5) 

