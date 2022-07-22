# source file: prog/_calllib.s1
import sys
import os
sys.path.append('sys')
from s1 import *

includePath(__file__, './lib/')
import rnd as R
                                                   # (1) 
includePath(__file__, './lib/')
import file as F
                                                   # (2) 
includePath(__file__, './lib/')
import guid as G
                                                   # (3) 
includePath(__file__, './lib/')
import calculus as C
                                                   # (4) 
includePath(__file__, './lib/')
import vector as V
                                                   # (5) 
includePath(__file__, './lib/')
import obj as O
                                                   # (6) 
async def main():                                  # (8) 
    log('rUnif(5,10)=',R.rUnif(5,10))              # (9) 
    await F.copyText('data/test.txt','data/test2.txt') # (10) 
    log('rInt()=',R.rInt(10,20))                   # (11) 
    log('guid()=',G.guid())                        # (12) 
    log('diff(sin, PI/4)=',C.df(sin,(math.PI/4)))  # (13) 
    log('dot([1,2,3], [1,1,1])=',V.dot([1,2,3],[1,1,1])) # (14) 
    obj={'name':'snoopy','age':3}                  # (15) 
    obj2=O.copy(obj)                               # (16) 
    log('obj2=',obj2)                              # (17) 
                                                   # (8) 
if 'main' in globals():run(main)
