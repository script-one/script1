function* range(from, to, step=1) {
    for (let x=from; x<to; x+=step) {
        yield x
    }
}

let r = range(0, 10)
/*
while (1) {
    let v = r.next()
    if (v.done) break
    console.log('v=', v)
}
*/

for (let i of r) {
    console.log('i=', i)
}
