/*
export function match(exp, text) {
    let r = new RegExp(exp, 'g')
    r.lastIndex = 0
    return text.match(r)
}
*/
export function grep(exp, text, groupId=0) {
    const regex1 = RegExp(exp, 'g')
    let m, list=[]
    while ((m = regex1.exec(text)) !== null) {
        list.push(m[groupId]) 
    }
    return list
}

global.grep = grep
