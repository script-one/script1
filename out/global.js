// source file: prog/global.s1
import '../sys/s1.js'

global.log(`hello 你好!`);                       // (1) 
let x=3;                                           // (3) 
global.x=5;                                        // (5) 
log(`x=`,x);                                       // (7) 
log(`@x=`,global.x);                               // (8) 
if (typeof main == 'function') main()
