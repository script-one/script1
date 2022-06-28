# source file: prog/while.s1
import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), '..', 'sys'))
from s1 import *

def sum(n):                                        # (1) 
                                                   # (1) 
  i=1                                              # (2) 
  s=0                                              # (3) 
  while (i<=n):                                    # (4) 
                                                   # (4) 
    s=(s+i)                                        # (5) 
    i=(i+1)                                        # (6) 
                                                   # (4) 
                                                   # (4) 
  return s                                         # (8) 
                                                   # (1) 
log('sum(10)=',sum(10))                            # (11) 

