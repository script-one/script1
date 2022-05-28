window.global = window

export function log(...args) {
    console.log(...args)
}

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

export function map(a, f) {
    return a.map(f)
}

export function push(list, a) {
    list.push(a)
    return list
}

global.log = log
global.str = str
global.keys = keys
global.values = values
global.range = range
global.re = re
global.map = map
global.push = push
