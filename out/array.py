# source file: prog/array.s1
import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), '..', 'sys'))
from s1 import *

def mean(a):                                       # (1) 
  s=0.0;                                           # (2) 
  for x in a: s=(s+x);                             # (3) 
                                                   # (3) 
  return (s/a.length);                             # (4) 
                                                   # (1) 
log('mean([1 2 3 4 5])=${mean([1.0,2,3,4,5])}');   # (7) 
