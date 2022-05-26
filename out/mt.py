# source file: prog/mt.s1
import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), '..', 'sys'))
from s1 import *

e2c={'dog':'狗','cat':'貓','a':'一隻','the':'這隻','chase':'追','bite':'吃'} # (1) 
def translate(ewords):                             # (3) 
  cwords=[];                                       # (4) 
  for e in ewords:                                 # (5) 
    cwords.push(e2c[e]);                           # (6) 
                                                   # (5) 
                                                   # (5) 
  return cwords;                                   # (8) 
                                                   # (3) 
c=translate(['a','dog','chase','a','cat']);        # (11) 
log(c);                                            # (12) 

