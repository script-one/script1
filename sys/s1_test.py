from s1 import *

name="ccc"
log("hello", name)

log('hello', 'ccc')
log('hello', 'ccc', '!')
log('hello', 'ccc', '!', 32, [])
map1 = {'a':1, 'b':2, 'c':[3,4]}
log(keys(map1))
log(values(map1))
log(list(range(1,10)))
log(list(range(1,10,2)))

log('null=', null)

glob.x = 3
log('@x=', glob.x)

def g1():
    glob.x = 5

g1()
log('@x=', glob.x)

