// source file: prog/_copy.s1
import '../sys/s1.js'

import * as O from './lib/obj.js';                 // (1) 
let a=['a',1];                                     // (2) 
let b=['b',a];                                     // (3) 
let d=O.copy(b);                                   // (5) 
b[0]='b1';                                         // (6) 
a[1]=2;                                            // (7) 
log('a=',a);                                       // (9) 
log('b=',b);                                       // (10) 
log('d=',d);                                       // (12) 
if (typeof main == 'function') main()
