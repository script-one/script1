window.global = window

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

export function push(list, a) {
    list.push(a)
    return list
}

export function len(list) {
    return list.length
}

export function error(msg) {
    return Error(msg)
}

export function array(n) {
    return new Array(n)
}

global.str = str
global.keys = keys
global.values = values
global.range = range
global.push = push
global.len = len
global.error = error
global.array = array
