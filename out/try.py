# source file: prog/try.s1
import sys
import os
sys.path.append('sys')
from s1 import *

try:                                               # (1) 
    raise error('Error')                           # (2) 
                                                   # (1) 
except BaseException as e:                         # (3) 
    log(e)                                         # (4) 
                                                   # (3) 
                                                   # (1) 

