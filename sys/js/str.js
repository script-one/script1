export function str(o) {
    if (o.__str) return o.__str()
    return o.toString()
}

export function substr(str, i, len) {
    return str.substr(i, len)
}

global.str = str
global.substr = substr
