export function date(year, month, day) {
    return new Date(year, month, day)
}

/*
export function time(year, month, day, hour, minute, second, millsecond) {
    return new Date(year, month, day, hour, minute, second, millsecond)
}
*/

export function now() {
    return new Date()
}

export function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

global.date = date
global.now = now
// global.time = time
global.sleep = sleep
