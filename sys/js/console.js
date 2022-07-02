export function log(...args) {
    console.log(...args)
}

export function warning(...args) {
    console.error(...args)
}

export function input(message) {
    return prompt(message)
}

global.input = input
global.log = log
global.warning = warning
