// source file: prog/global.s1
import '../sys/s1.js'

log('hello 你好!');                              // (1) 
let x=3;                                           // (3) 
glob.x=5;                                          // (5) 
log('x=',x);                                       // (7) 
log('@x=',glob.x);                                 // (8) 
if (typeof main == 'function') main()
