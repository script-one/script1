# source file: prog/regexp.s1
import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), '..', 'sys'))
from s1 import *

text='name:ccc age:52 height:166 weight:60';       # (1) 
r1=re('\\d+','g');                                 # (2) 
log(text.match(r1));                               # (4) 

