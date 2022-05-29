// source file: prog/sum.s1
import '../sys/s1.js'

function sum(n){                                   // (1) 
  let s=0;                                         // (2) 
  for (let i of range(1,(n+1))) s=(s+i);           // (3) 
                                                   // (3) 
  return s;                                        // (4) 
}                                                  // (1) 
log(`sum(10)=`,sum(10));                           // (7) 
if (typeof main == 'function') main()
