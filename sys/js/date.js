export function date(year, month, day) {
    return new Date(year, month, day)
}

export function today() {
    return new Date()
}

export function time(year, month, day, hour, minute, second, millsecond) {
    return new Date(year, month, day, hour, minute, second, millsecond)
}

export function now() {
    return Date.now()
}

global.date = date
global.today = today
global.now = now
global.time = time
