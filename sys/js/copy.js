export function copy(o) {
    if (o instanceof Array) {
        return o.slice(0)
    } else if (o instanceof Object) {
        return {...o}
    } else {
        return o
    }
}

export function deepCopy(o) {
    return JSON.parse(JSON.stringify(o))
}

global.copy = copy
global.deepCopy = deepCopy
