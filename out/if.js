// source file: prog/if.s1
import '../sys/s1.js'

export function max(x,y)                           // (1) 
{                                                  // (1) 
    return (x>y)?x:y;                              // (1) 
}                                                  // (1) 
let min=(x,y)=>(x<y)?x:y;                          // (2) 
log('max(3,5)=',max(3,5));                         // (4) 
log('min(3,5)=',min(3,5));                         // (5) 
if (typeof main == 'function') main()
