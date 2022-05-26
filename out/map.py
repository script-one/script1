# source file: prog/map.s1
import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), '..', 'sys'))
from s1 import *

ccc={'name':'ccc','age':52}                        # (1) 
log(ccc);                                          # (2) 
e2c={'dog':'狗','cat':'貓','a':'一隻','the':'這隻','chase':'追','bite':'吃'} # (4) 
log(e2c);                                          # (5) 

