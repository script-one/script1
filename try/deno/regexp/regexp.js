let text = 'name:ccc age:52 height:166 weight:60'
let r1 = new RegExp('\\d+', 'g')

console.log(text.match(r1))
