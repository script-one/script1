export function date(year, month, day) {
    return new Date(year, month, day)
}

export function time(year, month, day, hour, minute, second, millsecond) {
    return new Date(year, month, day, hour, minute, second, millsecond)
}

export function now() {
    return new Date()
}

global.date = date
global.now = now
global.time = time
