import sys, os
import random as R
import math
import inspect

null =  None

class Glob:
    def __init__(self):
        pass

glob = Glob()

def addPath(path):
    sys.path.append(path)

def includePath(file, path):
    sys.path.append(os.path.join(os.path.dirname(file), path))

def run(f):
    if inspect.iscoroutinefunction(f):
        asyncio.run(f())
    else:
        f()

# base

def push(l, a):
    l.append(a)
    return l

def keys(dict):
    return dict.keys()

def values(dict):
    return dict.values()

# len : default
# range : default

def error(msg):
    return Exception(msg)

def random():
    return R.random()

def floor(x):
    return math.floor(x)

# array

def array(n, value):
    return [value] * 5

def join(a, spliter=' '):
    return spliter.join([str(x) for x in a])

pymap = map
pyfilter = filter
from functools import reduce
pyreduce = reduce

def map(a, f):
    return list(pymap(f, a))

def filter(a, f):
    return list(pyfilter(f, a))

def reduce(a, f, init):
    return list(pyreduce(f, a, init))

# console

import logging

def log(*args):
    print(join(args))

def warning(*args):
    logging.warning(join(args))

# input:default

import datetime

def date(year, month, day):
    return datetime.datetime(year, month, day)

def now():
    return datetime.datetime.now()

# sleep:default

import asyncio
from aiofile import async_open

# fs -- https://www.twilio.com/blog/working-with-files-asynchronously-in-python-using-aiofiles-and-asyncio
async def readText(fpath):
    async with async_open(fpath, mode='r') as f:
        text = await f.read()
        return text

async def writeText(fpath, text):
    async with async_open(fpath, mode='w') as f:
        await f.write(text)

# hash -- https://docs.python.org/3/library/hashlib.html

# json -- https://www.w3schools.com/python/python_json.asp
import json

def toJson(o):
    return json.dumps(o)

def fromJson(text):
    return json.loads(text)


import math as M

# math -- https://docs.python.org/3/library/math.html

class math:
    PI = M.pi

sin = M.sin
cos = M.cos
tan = M.tan
asin = M.asin
acos = M.acos
atan = M.atan
exp = M.exp
sqrt = M.sqrt
floor = M.floor
ceil = M.ceil
ln = M.log

# regexp -- https://docs.python.org/3/library/re.html

# sqlite -- https://docs.python.org/3/library/sqlite3.html

# str -- https://www.freecodecamp.org/news/how-to-substring-a-string-in-python/

def substr(str1, i, len):
    return str1[i:i+len]
