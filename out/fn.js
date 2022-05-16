// source file: prog/fn.s1
import '../sys/s1.js'

let inc=function (x) {                             // (1) 
  return (x+1)                                     // (1) 
}                                                  // (1) 
let add=function (x,y) {                           // (3) 
  return (x+y)                                     // (3) 
}                                                  // (3) 
print('inc(2)=',inc(2))                            // (5) 
print('add(2,3)=',add(2,3))                        // (6) 

