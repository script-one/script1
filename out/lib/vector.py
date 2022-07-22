# source file: prog/lib/vector.s1
import sys
import os
sys.path.append('sys')
from s1 import *

def map2(a,b,f):                                   # (1) 
    alen=len(a)                                    # (2) 
    c=array(alen)                                  # (3) 
    for i in range(0,alen):                        # (4) 
        c[i]=f(a[i],b[i])                          # (5) 
                                                   # (4) 
                                                   # (4) 
    return c                                       # (7) 
                                                   # (1) 
def dot(a,b):                                      # (10) 
    alen=len(a)                                    # (11) 
    r=0                                            # (12) 
    for i in range(0,alen):                        # (13) 
        r=(r+(a[i]*b[i]))                          # (14) 
                                                   # (13) 
                                                   # (13) 
    return r                                       # (16) 
                                                   # (10) 
def neg(a):                                        # (19) 
    return map(a,lambda a:- a)                     # (20) 
                                                   # (19) 
def add(a,b):                                      # (23) 
    return map2(a,b,lambda a,b:(a+b))              # (24) 
                                                   # (23) 

