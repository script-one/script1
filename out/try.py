# source file: prog/try.s1
import sys
import os
sys.path.append('sys')
from s1 import *

try:                                               # (1) 
    throw error('Error')                           # (2) 
                                                   # (1) 
except error:                                      # (3) 
    log(error)                                     # (4) 
                                                   # (3) 
                                                   # (1) 

