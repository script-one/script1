# source file: prog/lib/random.s1
import sys
sys.path.append('sys')
from s1 import *

def rUnif(min,max):                                # (1) 
    return (min+(random()*(max-min)))              # (2) 
                                                   # (1) 
def rInt(min,max):                                 # (5) 
    return floor(rUnif(min,max))                   # (6) 
                                                   # (5) 
def rChoose(a):                                    # (9) 
    return a[rInt(0,len(a))]                       # (10) 
                                                   # (9) 

