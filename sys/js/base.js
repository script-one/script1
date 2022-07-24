window.global = window
window.glob = {}

export function keys(o) {
    if (o instanceof Map || o instanceof Set) return Array.from(o.keys())
    return Object.keys(o)
}

export function values(o) {
    if (o instanceof Map || o instanceof Set) return Array.from(o.keys())
    return Object.keys(o)
}

/*
export function range(from, to, step=1) {
    let list=[]
    for (let i=from; i<to; i+=step) {
        list.push(i);
    }
    return list;
}
*/

export function* range(from, to, step=1) {
    for (let x=from; x<to; x+=step) {
        yield x
    }
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

// like python list(...)
export function list(a) {
    return Array.from(a)
}

global.keys = keys
global.values = values
global.range = range
global.push = push
global.len = len
global.error = error


