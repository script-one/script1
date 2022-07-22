// source file: prog/_regexp.s1
import '../sys/s1.js'

let text='name:ccc age:52 height:166 weight:60';   // (1) 
log(grep('\\d+',text));                            // (3) 
log(grep('(\\w+:\\d+)',text,1));                   // (4) 
if (typeof main == 'function') main()
