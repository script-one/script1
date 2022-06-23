export function input(message) {
    return prompt(message)
}

export function log(...args) {
    console.log(...args)
}

export function warning(...args) {
    console.error(...args)
}

global.input = input
global.log = log
global.warning = warning
