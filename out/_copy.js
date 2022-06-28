// source file: prog/_copy.s1
import '../sys/s1.js'

let a=['a',1];                                     // (1) 
let b=['b',a];                                     // (2) 
let c=copy(b);                                     // (3) 
let d=deepCopy(b);                                 // (4) 
b[0]='b1';                                         // (5) 
a[1]=2;                                            // (6) 
log('a=',a);                                       // (8) 
log('b=',b);                                       // (9) 
log('c=',c);                                       // (10) 
log('d=',d);                                       // (11) 
if (typeof main == 'function') main()
