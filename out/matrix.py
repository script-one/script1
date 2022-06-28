# source file: prog/matrix.s1
import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), '..', 'sys'))
from s1 import *

a=[[1,2],[4,5]]                                    # (1) 
b=[[1,1],[1,1]]                                    # (2) 
log('a=',a)                                        # (4) 
log('b=',b)                                        # (5) 

