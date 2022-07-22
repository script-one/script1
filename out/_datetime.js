// source file: prog/_datetime.s1
import '../sys/s1.js'

let d1=now();                                      // (1) 
log(d1);                                           // (2) 
log(str(d1));                                      // (3) 
if (typeof main == 'function') main()
