// source file: lib/calculus.s1
import '../sys/s1.js'

function diff(f,x,h=step)                          // (2) 
{                                                  // (2) 
  let dy=(f((x+h))-f(x));                          // (3) 
  return (dy/h);                                   // (4) 
}                                                  // (2) 
function integral(f,a,b,h=step)                    // (8) 
{                                                  // (8) 
  let area=0.0;                                    // (9) 
  for (let x of range(a,b,h))                      // (10) 
  {                                                // (10) 
    area=(area+(f(x)*h));                          // (11) 
  };                                               // (10) 
                                                   // (10) 
  return area;                                     // (13) 
}                                                  // (8) 

