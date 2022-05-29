// source file: prog/fn.s1
import '../sys/s1.js'

function inc(x){                                   // (1) 
  return (x+1);                                    // (1) 
}                                                  // (1) 
let add=function (x,y) { return (x+y) }            // (3) 
log('inc(2)=',inc(2));                             // (5) 
log('add(2,3)=',add(2,3));                         // (6) 
if (typeof main == 'function') main()
