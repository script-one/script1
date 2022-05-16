// source file: prog/array.s1
import '../sys/s1.js'

function mean(a) {                       // (1) 
  let s=0                                // (2) 
  for (let i in a) s=(s+a[i])            // (3) 
                                         // (3) 
  return (s/a.length)                    // (4) 
}                                        // (1) 
print('mean([1 2 3 4 5])=',mean([1,2,3,4,5])) // (7) 

