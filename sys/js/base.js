window.global = window

export function keys(o) {
    if (o instanceof Map || o instanceof Set) return Array.from(o.keys())
    return Object.keys(o)
}

export function values(o) {
    if (o instanceof Map || o instanceof Set) return Array.from(o.keys())
    return Object.keys(o)
}

export function range(from, to, step=1) {
    let list=[]
    for (let i=from; i<to; i+=step) {
        list.push(i);
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

export function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

export function join(list, spliter) {
    return list.join(spliter)
}

global.keys = keys
global.values = values
global.range = range
global.push = push
global.len = len
global.error = error
global.sleep = sleep
global.join = join

