# source file: prog/lib/calculus.s1
import sys
import os
sys.path.append('sys')
from s1 import *

def df(f,x,h=0.001):                               # (3) 
    dy=(f((x+h))-f(x))                             # (4) 
    return (dy/h)                                  # (5) 
                                                   # (3) 
def integral(f,a,b,h=0.001):                       # (9) 
    area=0.0                                       # (10) 
    for x in range(a,b,h):                         # (11) 
        area=(area+(f(x)*h))                       # (12) 
                                                   # (11) 
                                                   # (11) 
    return area                                    # (14) 
                                                   # (9) 

