# source file: prog/lib/guid.s1
import sys
import os
sys.path.append('sys')
from s1 import *

includePath(__file__, './')
import rnd as R
                                                   # (1) 
def randomChar(chars):                             # (3) 
    i=R.rInt(0,len(chars))                         # (4) 
    return chars[i]                                # (5) 
                                                   # (3) 
def randomStr(chars,n):                            # (8) 
    list=[]                                        # (9) 
    clen=len(chars)                                # (10) 
    for i in range(0,n):                           # (11) 
        ci=R.rInt(0,clen)                          # (12) 
        push(list,chars[ci])                       # (13) 
                                                   # (11) 
                                                   # (11) 
    return join(list,'')                           # (15) 
                                                   # (8) 
BASE='0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ' # (18) 
def baseChars(base):                               # (20) 
    return substr(BASE,0,base)                     # (21) 
                                                   # (20) 
def randomBase(base,len):                          # (24) 
    return randomStr(baseChars(base),len)          # (25) 
                                                   # (24) 
def s4():                                          # (28) 
    return randomBase(16,4)                        # (29) 
                                                   # (28) 
def guid():                                        # (33) 
    return (s4()+(s4()+('-'+(s4()+('-'+(s4()+('-'+(s4()+('-'+(s4()+(s4()+s4()))))))))))) # (34) 
                                                   # (33) 

