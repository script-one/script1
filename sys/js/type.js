
export function float(str) {
    return parseFloat(str)
}

export function equal(obj1, obj2) {
    return (obj1 == obj2 || JSON.stringify(obj1) == JSON.stringify(obj2))
}

export function isDefined(x) {
    return x == null
}

export function isInstanceOf(obj, cls) {
    return obj instanceof cls
}

export function isTypeEqual(obj1, obj2) {
    return typeof(obj1) == typeof(obj2)
}

global.float = float
global.equal = equal
global.isDefined = isDefined
global.isInstanceOf = isInstanceOf
global.isTypeEqual = isTypeEqual
global.isDefined = isDefined
global.isDefined = isDefined
