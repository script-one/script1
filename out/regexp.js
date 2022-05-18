// source file: prog/regexp.s1
import '../sys/s1.js'

let text=`name:ccc age:52 height:166 weight:60`;   // (1) 
let r1=re(`\\d+`,`g`);                             // (2) 
log(text.match(r1));                               // (4) 
if (typeof main == 'function') main()
