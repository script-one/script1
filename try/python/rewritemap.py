print(list(map(lambda x:x*x, [1,2,3])))

pymap = map

def map(a, f):
    return pymap(f, a)

print(list(map([1,2,3], lambda x:x*x)))
