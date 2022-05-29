// source file: prog/array.s1
import '../sys/s1.js'

function mean(a){                                  // (1) 
  let s=0.0;                                       // (2) 
  for (let x of a) s=(s+x);                        // (3) 
                                                   // (3) 
  return (s/a.length);                             // (4) 
}                                                  // (1) 
log(`mean([1 2 3 4 5])=${mean([1.0,2,3,4,5])}`);   // (7) 
if (typeof main == 'function') main()
