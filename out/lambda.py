# source file: prog/lambda.s1
import sys
import os
sys.path.append('sys')
from s1 import *

def inc(x):                                        # (1) 
    return (x+1)                                   # (1) 
                                                   # (1) 
a=[1,2,3]                                          # (3) 
b=map(a,lambda x:(x*x))                            # (4) 
c=map(a,inc)                                       # (5) 
log('a=',a)                                        # (7) 
log('b=',b)                                        # (8) 
log('c=',c)                                        # (9) 

