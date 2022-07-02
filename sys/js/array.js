export function array(n, value) {
    let a = new Array(n)
    a.fill(value)
    return a
}

export function join(list, spliter) {
    return list.join(spliter)
}

export function map(a, f) {
    return a.map(f)
}

export function filter(a, f) {
    return a.filter(f)
}

export function reduce(a, f, init) {
    return a.reduce(f, init)
}

global.array = array
global.join = join
global.reduce = reduce
global.filter = filter
global.map = map
