export function map(a, f) {
    return a.map(f)
}

export function filter(a, f) {
    return a.filter(f)
}

export function reduce(a, f, init) {
    return a.reduce(f, init)
}

global.reduce = reduce
global.filter = filter
global.map = map
