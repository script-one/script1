import sys, os
import random as R
import math

null =  None

def addPath(path):
    sys.path.append(path)

def includePath(path):
    sys.path.append(os.path.join(os.path.dirname(__file__), path))

def log(*args):
    [print(arg, end='') for arg in args]
    print(' ')

def push(l, a):
    l.append(a)
    return l

def map(l, f):
    # cannot use python keyword map() here
    # l = map(f, l)
    return [f(x) for x in l]

def random():
    return R.random()

def floor(x):
    return math.floor(x)


"""
export function str(o) {
    if (o.__str) return o.__str()
    return o.toString()
}

export function keys(o) {
    if (o instanceof Map || o instanceof Set) return Array.from(o.keys())
    return Object.keys(o)
}

export function values(o) {
    if (o instanceof Map || o instanceof Set) return Array.from(o.keys())
    return Object.keys(o)
}

export function range(from, to, step=1) {
    let list=[], i=from;
    while (i<to) {
        list.push(i);
        i+=step;
    }
    return list;
}

export function re(exp, attr) {
    let r = new RegExp(exp, attr)
    r.lastIndex = 0
    return r
}

global.log = log
global.str = str
global.keys = keys
global.values = values
global.range = range
global.re = re
"""
