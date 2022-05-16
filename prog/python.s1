import 'https://deno.land/x/python/mod.ts' as p

python := p.python
np := python['import']('numpy')

xpoints := np.array([1, 8])
ypoints := np.array([3, 10])

print('xpoints=', xpoints)
print('ypoints=', ypoints)

plt := python['import']('matplotlib.pyplot')
plt.plot(xpoints, ypoints)
plt.show()
