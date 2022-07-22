# source file: prog/array.s1
import sys
import os
sys.path.append('sys')
from s1 import *

def mean(a):                                       # (1) 
    s=0.0                                          # (2) 
    for x in a: s=(s+x)                            # (3) 
                                                   # (3) 
    return (s/len(a))                              # (4) 
                                                   # (1) 
log('mean([1 2 3 4 5])=',mean([1.0,2,3,4,5]))      # (7) 

