# source file: prog/obj.s1
import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), '..', 'sys'))
from s1 import *

ccc={'name':'ccc','age':52,'str':lambda :('name='+(this.name+(' age='+this.age)))} # (1) 
log(ccc.str());                                    # (9) 

