// source file: prog/if_t.s1
import '../sys/s1.js'

function max(x,y) {                                // (1) 
  if (x>y) return x;                               // (1) 
 else return y;                                    // (1) 
;                                                  // (1) 
}                                                  // (1) 
print(`max(3 5)=${max(3,5)}`);                     // (3) 
if (typeof main == 'function') main()
