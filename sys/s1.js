window.global = window

export function print(...args) {
    console.log(...args)
}

export function str(o) {
    if (o.__str) return o.__str();
    return o.toString()
}

global.print = print
global.str = str
