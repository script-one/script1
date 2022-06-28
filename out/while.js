// source file: prog/while.s1
import '../sys/s1.js'

function sum(n)                                    // (1) 
{                                                  // (1) 
  let i=1;                                         // (2) 
  let s=0;                                         // (3) 
  while (i<=n)                                     // (4) 
  {                                                // (4) 
    s=(s+i);                                       // (5) 
    i=(i+1);                                       // (6) 
  };                                               // (4) 
                                                   // (4) 
  return s;                                        // (8) 
}                                                  // (1) 
log('sum(10)=',sum(10));                           // (11) 
if (typeof main == 'function') main()
