export function toJson(o) {
    return JSON.stringify(o, null, 2)
}

export function fromJson(str) {
    return JSON.parse(str)
}

global.toJson = toJson
global.fromJson = fromJson
