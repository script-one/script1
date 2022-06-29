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

export function array(n, value) {
    let a = new Array(n)
    a.fill(value)
    return a
}

export function isDefined(x) {
    return x == null
}

export function float(str) {
    return parseFloat(str)
}

export function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

export function join(list, spliter) {
    return list.join(spliter)
}

export function substr(str, i, len) {
    return str.substr(i, len)
}

global.str = str
global.keys = keys
global.values = values
global.range = range
global.push = push
global.len = len
global.error = error
global.array = array
global.isDefined = isDefined
global.float = float
global.sleep = sleep
global.join = join
global.substr = substr
