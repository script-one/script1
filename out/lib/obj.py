# source file: prog/lib/obj.s1
import sys
import os
sys.path.append('sys')
from s1 import *

def copy(o):                                       # (1) 
    return fromJson(toJson(o))                     # (2) 
                                                   # (1) 

