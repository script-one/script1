// source file: prog/_datetime.s1
import '../sys/s1.js'

let d1=today();                                    // (1) 
log(d1);                                           // (2) 
log(d1.toDateString());                            // (3) 
if (typeof main == 'function') main()
