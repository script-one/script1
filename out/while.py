# source file: prog/while.s1
import sys
import os
sys.path.append('sys')
from s1 import *

def sum(n):                                        # (1) 
    i=1                                            # (2) 
    s=0                                            # (3) 
    while (i<=n):                                  # (4) 
        s=(s+i)                                    # (5) 
        i=(i+1)                                    # (6) 
                                                   # (4) 
                                                   # (4) 
    return s                                       # (8) 
                                                   # (1) 
def main():                                        # (11) 
    log('sum(10)=',sum(10))                        # (12) 
                                                   # (11) 
if 'main' in globals():run(main)
