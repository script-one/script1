# source file: prog/try.s1
import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), '..', 'sys'))
from s1 import *

try:                                               # (1) 
  throw Error('Error');                            # (2) 
                                                   # (1) 
except error:                                      # (3) 
  log(error);                                      # (4) 
                                                   # (3) 
                                                   # (1) 

