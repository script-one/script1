// source file: prog/lambda.s1
import '../sys/s1.js'

function inc(x)                                    // (1) 
{                                                  // (1) 
  return (x+1);                                    // (1) 
}                                                  // (1) 
let a=[1,2,3];                                     // (3) 
let b=map(a,(x)=>(x*x));                           // (4) 
let c=map(a,inc);                                  // (5) 
log('a=',a);                                       // (7) 
log('b=',b);                                       // (8) 
log('c=',c);                                       // (9) 
if (typeof main == 'function') main()
