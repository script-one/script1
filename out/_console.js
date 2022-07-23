// source file: prog/_console.s1
import '../sys/s1.js'

let user=input('user:');                           // (1) 
log('user=',user);                                 // (3) 
error('error: test error !');                      // (4) 
if (typeof main == 'function') main()
