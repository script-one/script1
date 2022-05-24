sq = lambda x:x*x

def f(x):
    return x*x

sq2 = lambda x: f(x)

print(sq(2))
print(sq2(2))