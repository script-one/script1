// source file: prog/cond.s1
import '../sys/s1.js'

let max=(x,y)=>(x>y)?x:y;                          // (1) 
log('max(3,5)=',max(3,5));                         // (3) 
if (typeof main == 'function') main()
