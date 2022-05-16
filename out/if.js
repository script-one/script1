// source file: prog/if.s1
import '../sys/s1.js'

let max=function (x,y) {                           // (1) 
  if (x>y) return x                                // (1) 
 else return y                                     // (1) 
                                                   // (1) 
}                                                  // (1) 
print('max(3 5)=',max(3,5))                        // (3) 

