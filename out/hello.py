# source file: prog/hello.s1
import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), '..', 'sys'))
from s1 import *

name='script1';                                    # (1) 
log(('hello '+name));                              # (2) 

