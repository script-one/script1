// source file: prog/sum.s1
import '../sys/s1.js'

let sum=function (n) {                   // (1) 
  let s=0                                // (2) 
  for (let i=1;i<=n;i++) s=(s+i)         // (3) 
                                         // (3) 
  return s                               // (4) 
}                                        // (1) 
print('sum(10)=',sum(10))                // (7) 

