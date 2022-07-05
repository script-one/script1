import sys 
import os

def includePath(path):
    sys.path.append(os.path.join(os.path.dirname(__file__), path))

includePath('lib')

import lib1 as L
L.hello()

includePath('lib/math')
import mod as M
print('add(2,3)=', M.add(2,3))
