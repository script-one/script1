# source file: prog/sum.s1
import sys
import os
sys.path.append('sys')
from s1 import *

def sum(n):                                        # (1) 
    s=0                                            # (2) 
    for i in range(1,(n+1)):s=(s+i)                # (3) 
                                                   # (3) 
    return s                                       # (4) 
                                                   # (1) 
log('sum(10)=',sum(10))                            # (7) 

